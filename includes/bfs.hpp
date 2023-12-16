#ifndef BFS_HPP
#define BFS_HPP

#include <queue>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <functional>

#include "safe_scan.hpp"


namespace se{

template <typename T> 
class Bfs : public SafeScan<T>
{
public:
    Bfs();
    ~Bfs() = default;
    Bfs(const Bfs&) = default;
    Bfs& operator= (const Bfs&) = default;
    
    void add(const T& element)override;
    bool get(T& t,const std::function<bool(size_t m_numSleeping)>& status_member_handleer)override;
    bool empty()const override;
    void stop()override;

private:
    std::queue<T> m_queue;
    mutable std::shared_mutex m_mtx;
    std::condition_variable_any m_condition;
    std::atomic_size_t m_numSleeping;
    std::atomic_bool m_status;
};

} // namespace se
#include "bfs.inl"
#endif
