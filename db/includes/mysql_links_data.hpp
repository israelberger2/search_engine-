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
    std::string getLink(int id)const override;
    std::vector<std::string> getLinks(std::vector<int> linksID)const override;
};
 
} //db
#endif
