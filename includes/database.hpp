#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <vector>

#include "links_map_get.hpp"
#include "indexer_get.hpp"


namespace se{

class Database
{
public:
    static Database& getInstance(IndexerGet& indexer, LinksMapGet& links);

    ~Database() = default;
    Database(const Database&) = delete;
    Database& operator= (const Database&) = delete;

    std::vector<std::pair<std::string, size_t>> get_related_links(const std::string& key)const;
    size_t get_links_size()const;
    size_t get_words_size()const;
 
private:
    explicit Database(IndexerGet& indexer, LinksMapGet& links);

private:
    static Database* m_database;
    IndexerGet& m_indexer;
    LinksMapGet& m_links;
};

} // namespace se
#endif
