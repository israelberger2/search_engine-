#include "safe_queue.hpp"

namespace se{

template <typename T>
SafeQueue<T>::SafeQueue()
: m_queue()
, m_mtx()
, m_condition()
, m_numSleeping(0)
, m_status(true)
{}

template <typename T>
bool SafeQueue<T>::empty()const
{
    std::shared_lock<std::shared_mutex> lock(m_mtx);
    return m_queue.empty();
}

template <typename T>
void SafeQueue<T>::setStatus()
{
    !m_status;
}

template <typename T>
void SafeQueue<T>::enqueue(const T& element)
{
    std::unique_lock<std::shared_mutex> lock(m_mtx);
    m_queue.push(element);
    m_condition.notify_all();
}

template <typename T>
bool SafeQueue<T>::dequeue(T& t,const std::function<bool(size_t m_numSleeping)>& status_member_handleer)
{
    std::unique_lock<std::shared_mutex> lock(m_mtx);
    while(m_queue.empty()){
        ++m_numSleeping;
        m_status =  status_member_handleer(m_numSleeping);
        m_condition.wait(lock, [&](){return m_status == false || !m_queue.empty();});
    }
    --m_numSleeping;
    
    if(!m_status){
        return false;
    }

    t = m_queue.front();
    m_queue.pop();

    return true;
}

template <typename T>
void SafeQueue<T>::notify()
{
    m_condition.notify_all();
}

} // namespace se
