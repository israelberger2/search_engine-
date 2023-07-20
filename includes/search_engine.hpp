#ifndef SEARCH_ENGINE_HPP
#define SEARCH_ENGINE_HPP

#include <memory>
#include <string>
#include <vector>

#include "searcher.hpp"
#include "database.hpp"
#include "links_map_get.hpp"
#include "indexer_get.hpp"
#include "client.hpp"
#include "sorter.hpp"


namespace se{

class SearchEngine
{
public:
    explicit SearchEngine(IndexerGet& word, LinksMapGet& links, Client& client, Isorter& sorter);
    ~SearchEngine() = default;
    SearchEngine(const SearchEngine&) = delete;
    SearchEngine& operator= (const SearchEngine&) = delete;
    
    void handle(size_t length)const;
    void opening_message()const;

private:
    std::shared_ptr<Searcher> m_searcher;
    Database& m_database;
    Client& m_client;
    Isorter& m_arranger;
};

} // namespace se
#endif
