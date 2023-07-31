#ifndef MYSQL_WORDLINKS_HPP
#define MYSQL_WORDLINKS_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include "word_links.hpp"
#include "connector.hpp"


namespace db
{

using WordsMap = std::unordered_map<std::string, int>;

class MysqlWordLinks : public WordLinks
{
public:                 
    MysqlWordLinks();
    ~MysqlWordLinks() = default;
    MysqlWordLinks(const MysqlWordLinks&) = delete;
    MysqlWordLinks& operator= (const MysqlWordLinks&) = delete;

    void insert(const WordsMap& words, const std::string& link)override;
    std::vector<int> getLinksForWord(const std::string& word)override;


private:
    Connector m_connector;
};

} // db
#endif