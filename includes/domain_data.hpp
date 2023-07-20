#ifndef DOMAINDATA_HPP 
#define DOMAINDATA_HPP 

#include <string>


namespace db{
 
class DomainData
{
public:
    virtual ~DomainData() = default;
    virtual int getIDAndInsert(const std::string& domain) = 0;
};
 
} //db
#endif
