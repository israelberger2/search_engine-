#ifndef SAFE_UNORDERED_MAP_HPP
#define SAFE_UNORDERED_MAP_HPP

#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <functional>
#include <vector>


namespace se{

template <typename Key, typename Value>
class SafeUnorderedMap
{
public:
    SafeUnorderedMap();
    ~SafeUnorderedMap() = default;
    SafeUnorderedMap& operator= (const SafeUnorderedMap&) = default;
    SafeUnorderedMap(SafeUnorderedMap&& other);
 
    Value operator[] (const Key& key);

    bool insert(Key key,Value value);
    bool is_here(const Key& key)const;
    Value get_dada(const Key& key)const;
    size_t size()const;
    void update(std::function<void(Value& v)>& updateKey ,Key& k);
    std::unordered_map<Key, Value> getMap()const;
    std::vector<Key> getKeys()const;
    void clear();
    
private:
    std::unordered_map<Key, Value> m_map;
    mutable std::shared_mutex m_mutex;
};

} // namespace se

#include "safe_unordered_map.inl"
#endif
