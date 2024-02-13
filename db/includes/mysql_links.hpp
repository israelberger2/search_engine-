#ifndef MYSQLLINKS_DATA 
#define MYSQLLINKS_DATA 

#include <string>
#include "connector.hpp"


namespace db{
 
class MysqlLinks 
{
public:
    MysqlLinks();
    ~MysqlLinks() = default;
    MysqlLinks(const MysqlLinks&) = delete;
    MysqlLinks& operator= (const MysqlLinks&) = delete;

    int insertAndGetLinkID(const std::string& link)const;
    std::string getLink(int id)const;
    std::vector<std::string> getLinks(std::vector<int> linksID)const;
};
 
} //db
#endif
