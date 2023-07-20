// #ifndef MYSQL_WORDLINKS_HPP
// #define MYSQL_WORDLINKS_HPP

// #include <string>

// #include "link.hpp"
// #include "word_links.hpp"
// #include "connector.hpp"


// namespace db
// {
    
// class MysqlWordLinks : public WordLinks
// {
// public:                 
//     MysqlWordLinks() = default;
//     ~MysqlWordLinks() = default;
//     MysqlWordLinks(const MysqlWordLinks&) = delete;
//     MysqlWordLinks operator= (const MysqlWordLinks&) = delete;

//     void insert(const std::string& word, const se::Link& link, int count)override;

// private:
//     Connector m_connector;
// };

// } // db
// #endif

#ifndef MYSQL_WORDLINKS_HPP
#define MYSQL_WORDLINKS_HPP

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
    MysqlWordLinks operator= (const MysqlWordLinks&) = delete;

    void insert(const WordsMap& words, const std::string& link)override;

private:
    Connector m_connector;
};

} // db
#endif