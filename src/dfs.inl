#include "dfs.hpp"


namespace se{

template <typename T>
Dfs<T>::Dfs()
: m_stack()
, m_mtx()
, m_condition()
, m_numSleeping(0)
, m_status(true)
{}

template <typename T>
bool Dfs<T>::empty()const
{
    std::shared_lock<std::shared_mutex> lock(m_mtx);
    return m_stack.empty();
}

template <typename T>
void Dfs<T>::add(const T& element)
{
    std::unique_lock<std::shared_mutex> lock(m_mtx);
    m_stack.push(element);
    m_condition.notify_all();
}

template <typename T>
bool Dfs<T>::get(T& t, const std::function<bool(size_t m_numSleeping)>& status_member_handleer)
{    
    std::unique_lock<std::shared_mutex> lock(m_mtx);
    while(m_stack.empty()){        
        ++m_numSleeping;
        m_status =  status_member_handleer(m_numSleeping);
        
        if(!m_status){
            m_condition.notify_all();            
            return false;
        }

        m_condition.wait(lock, [&](){return m_status == false || !m_stack.empty();});
        --m_numSleeping;
        
        if(!m_status){            
            return false;
        }
    }

    t = m_stack.top();
    m_stack.pop();
     
    return true;
}

template <typename T>
void Dfs<T>::stop()
{
    m_status = false;
    m_condition.notify_all();
}
  
} // namespace se
