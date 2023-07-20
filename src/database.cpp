  
#include "database.hpp"
 

namespace se{

Database* Database::m_database = nullptr;

Database::Database(IndexerGet& indexer, LinksMapGet& links)
: m_indexer(indexer)
, m_links(links)
{}

Database& Database::getInstance(IndexerGet& indexer, LinksMapGet& links)
{
    if(m_database == nullptr){
        m_database = new Database(indexer, links);
    } 
    
    return *m_database;
} 

std::vector<std::pair<std::string, size_t>> Database::get_related_links(const std::string& key)const
{
    std::vector<std::pair<std::string, size_t>> result;
    
    if(m_indexer.is_here(key)){
        result = m_indexer.get_links(key);
    }
     
    return result;
}

size_t Database::get_links_size()const
{
    return m_links.size();
}

size_t Database::get_words_size()const
{
    return m_indexer.size();
}

} // namespace se

