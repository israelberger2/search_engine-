#ifndef SAFE_SCAN_HPP
#define SAFE_SCAN_HPP

#include <functional>

namespace se{

template <typename T> 
class SafeScan 
{
public:
    virtual ~SafeScan() = default;
     
    virtual void add(const T& element) = 0;
    virtual bool get(T& t,const std::function<bool(size_t m_numSleeping)>& status_member_handleer) = 0;
    virtual bool empty()const = 0;
    virtual void stop() = 0;
};

} // namespace se
#endif