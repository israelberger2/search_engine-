#ifndef DFS_HPP
#define DFS_HPP

#include <stack>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <functional>

#include "safe_scan.hpp"


namespace se{

template <typename T> 
class Dfs : public SafeScan<T>
{
public:
    Dfs();
    ~Dfs() = default;
    Dfs(const  Dfs&) = default;
    Dfs& operator= (const  Dfs&) = default;
    
    void add(const T& element)override;
    bool get(T& t,const std::function<bool(size_t m_numSleeping)>& status_member_handleer)override;
    bool empty()const override;
    void stop()override;

private:
    std::stack<T> m_stack;
    mutable std::shared_mutex m_mtx;
    std::condition_variable_any m_condition;
    std::atomic_size_t m_numSleeping;
    std::atomic_bool m_status;
};

} // namespace se
#include "dfs.inl"
#endif
