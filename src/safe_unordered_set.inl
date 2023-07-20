

namespace se{

template <typename T> 
SafeUnorderedSet<T>::SafeUnorderedSet()
: m_set()
, m_mutx()
{}

template <typename T> 
bool SafeUnorderedSet<T>::insert(T element)
{
    std::unique_lock<std::shared_mutex> locker(m_mutx);
    auto status = m_set.insert(element);
    return status.second;
}

template <typename T> 
size_t SafeUnorderedSet<T>::size()const
{
    std::shared_lock<std::shared_mutex> locker(m_mutx);
    return m_set.size();
}

} // namespace se
