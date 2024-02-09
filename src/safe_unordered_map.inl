#include "safe_unordered_map.hpp"


namespace se{

template <typename Key, typename Value>
SafeUnorderedMap<Key, Value>::SafeUnorderedMap()
: m_map()
, m_mutex()
{}

template <typename Key, typename Value>
SafeUnorderedMap<Key, Value>::SafeUnorderedMap(SafeUnorderedMap&& other)
{
    m_map = std::move(other.m_map);
    other.m_map.clear();
}

template <typename Key, typename Value>
Value SafeUnorderedMap<Key, Value>::get(const Key& key)const
{
    std::shared_lock<std::shared_mutex> lock(m_mutex);
    
    auto res = m_map.find(key);
    return res->second;
}

template <typename Key, typename Value>
size_t SafeUnorderedMap<Key, Value>::size()const
{
    std::shared_lock<std::shared_mutex> lock(m_mutex);
    return m_map.size();
}

template <typename Key, typename Value>
Value SafeUnorderedMap<Key, Value>::operator[](const Key& key)
{
    std::shared_lock<std::shared_mutex> locker(m_mutex);
    return m_map[key];
}

template <typename Key, typename Value>
bool SafeUnorderedMap<Key, Value>::insert(Key key, Value value)
{
    std::unique_lock<std::shared_mutex> locker(m_mutex);

    auto res = m_map.insert({key,value});
    return res.second;
}

template <typename Key, typename Value>
std::unordered_map<Key, Value> SafeUnorderedMap<Key, Value>::getMap()const
{
    std::shared_lock<std::shared_mutex> locker(m_mutex);
    return m_map;
}

template <typename Key, typename Value>
std::vector<Key> SafeUnorderedMap<Key, Value>::getKeys()const
{
    std::shared_lock<std::shared_mutex> locker(m_mutex);

    std::vector<Key> result;
    result.reserve(m_map.size());

    for(auto k : m_map){
        result.push_back(k.first);
    }

    return result;
}

template <typename Key, typename Value>
void SafeUnorderedMap<Key, Value>::clear()
{
    m_map.clear();
}

} // namespase se
