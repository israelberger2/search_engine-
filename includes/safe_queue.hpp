#ifndef SAFE_QUEUE_HPP
#define SAFE_QUEUE_HPP

#include <queue>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <functional>

namespace se{

template <typename T> 
class SafeQueue
{
public:
    SafeQueue();
    ~SafeQueue() = default;
    SafeQueue(const SafeQueue&) = default;
    SafeQueue& operator= (const SafeQueue&) = default;
    
    void enqueue(const T& element);
    bool dequeue(T& t,const std::function<bool(size_t m_numSleeping)>& status_member_handleer);
    bool empty()const;
    void setStatus();
    void notify();

private:
    std::queue<T> m_queue;
    mutable std::shared_mutex m_mtx;
    std::condition_variable_any m_condition;
    std::atomic_size_t m_numSleeping;
    std::atomic_bool m_status;
};

} // namespace se
#include "safe_queue.inl"
#endif
