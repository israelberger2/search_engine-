#include "bfs.hpp"


namespace se{

template <typename T>
Bfs<T>::Bfs()
: m_queue()
, m_mtx()
, m_condition()
, m_numSleeping(0)
, m_status(true)
{}

template <typename T>
bool Bfs<T>::empty()const
{
    std::shared_lock<std::shared_mutex> lock(m_mtx);
    return m_queue.empty();
}

template <typename T>
void Bfs<T>::add(const T& element)
{
    std::unique_lock<std::shared_mutex> lock(m_mtx);
    m_queue.push(element);
    m_condition.notify_all();
}

 
template <typename T>
bool Bfs<T>::get(T& t, const std::function<bool(size_t m_numSleeping)>& status_member_handleer)
{
    std::unique_lock<std::shared_mutex> lock(m_mtx);
    while(m_queue.empty()){
        ++m_numSleeping;
        m_status =  status_member_handleer(m_numSleeping);
        if(!m_status){
            m_condition.notify_all();
            return false;
        }

        m_condition.wait(lock, [&](){return !m_status || !m_queue.empty();});
        --m_numSleeping;
        
        if(!m_status){
            return false;
        }
    }

    t = m_queue.front();
    m_queue.pop();

    return true;
}

template <typename T>
void Bfs<T>::stop()
{
    m_status = false;
    m_condition.notify_all();
}

} // namespace se
