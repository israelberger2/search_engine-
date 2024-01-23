#ifndef SAFE_UNORDERED_SET_HPP
#define SAFE_UNORDERED_SET_HPP

#include <unordered_set>
#include <mutex>
#include <shared_mutex>


namespace se{

template <typename T>   
class SafeUnorderedSet
{
public:
    SafeUnorderedSet();
    ~SafeUnorderedSet();
    SafeUnorderedSet(const SafeUnorderedSet&) = default;
    SafeUnorderedSet& operator= (const SafeUnorderedSet&) = default;

    bool insert(T element);
    size_t size()const;

private:
    std::unordered_set<T> m_set;
    mutable std::shared_mutex m_mutx;
};

} // namespace se
#include "safe_unordered_set.inl"
#endif
