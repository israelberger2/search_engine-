#ifndef SEARCH_ENGINE_HPP
#define SEARCH_ENGINE_HPP

#include <memory>
#include <string>
#include <vector>

#include "searcher.hpp"
#include "client.hpp"
#include "sorter.hpp"


namespace se{

class SearchEngine
{
public:
    explicit SearchEngine(std::shared_ptr<db::Searcher> searcher, Client& client, Isorter& sorter);
    ~SearchEngine() = default;
    SearchEngine(const SearchEngine&) = delete;
    SearchEngine& operator= (const SearchEngine&) = delete;
    
    void handle(size_t length)const;
    bool createQueriesVectors(std::vector<std::string>& positive, std::vector<std::string>& negative, const std::vector<std::string>& input)const;

private:
    std::shared_ptr<db::Searcher> m_searcher;
    Client& m_client;
    Isorter& m_arranger;
};

} // namespace se
#endif
