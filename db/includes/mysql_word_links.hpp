#ifndef MYSQL_WORDLINKS_HPP
#define MYSQL_WORDLINKS_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include "word_links.hpp"
#include "safe_unordered_map.hpp"


namespace db
{

using Map = std::unordered_map<std::string, int>;

class MysqlWordLinks : public WordLinks
{
public:                 
    MysqlWordLinks();
    ~MysqlWordLinks() = default;
    MysqlWordLinks(const MysqlWordLinks&) = delete;
    MysqlWordLinks& operator= (const MysqlWordLinks&) = delete;

    void insert(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const override;
    void insert(const Map& words, const std::string& link)const override;
    std::vector<std::string> getLinksContainingWord(const std::string& word)const override;
 
private:
    std::string createJsonPages(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const;
};

} // db
#endif