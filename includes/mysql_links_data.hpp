// #ifndef MYSQLLINKS_DATA 
// #define MYSQLLINKS_DATA 

// #include "links_data.hpp"
// #include "connector.hpp"
// #include "link.hpp"


// namespace db{
 
// class MysqlLinksData : public LinksData
// {
// public:
//     MysqlLinksData() = default;
//     ~MysqlLinksData() = default;
//     MysqlLinksData(const MysqlLinksData&) = delete;
//     MysqlLinksData& operator= (const MysqlLinksData&) = delete;

//     int insertAndGetLinkID(const se::Link& link)const override;

// private:
//     Connector m_connector;
// };
 
// } //db
// #endif



#ifndef MYSQLLINKS_DATA 
#define MYSQLLINKS_DATA 

#include <string>

#include "links_data.hpp"
#include "connector.hpp"


namespace db{
 
class MysqlLinksData : public LinksData
{
public:
    MysqlLinksData();
    ~MysqlLinksData() = default;
    MysqlLinksData(const MysqlLinksData&) = delete;
    MysqlLinksData& operator= (const MysqlLinksData&) = delete;

    int insertAndGetLinkID(const std::string& link)const override;

private:
    Connector m_connector;
};
 
} //db
#endif