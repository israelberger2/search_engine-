#ifndef MYSQL_DOMAUNDATA_HPP 
#define MYSQL_DOMAUNDATA_HPP 

#include "domain_data.hpp"
#include "connector.hpp"


namespace db{
 
class MysqlDomainData : public DomainData
{
public:
    MysqlDomainData() = default;
    ~MysqlDomainData() = default;
    MysqlDomainData(const MysqlDomainData&) = delete;
    MysqlDomainData& operator= (const MysqlDomainData&) = delete;

    int getIDAndInsert(const std::string& domain)override;

private:
    Connector m_connector;
};
 
} //db
#endif
