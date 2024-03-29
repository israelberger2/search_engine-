#ifndef SEARCH_ENGINE_HPP
#define SEARCH_ENGINE_HPP

#include <memory>
#include <string>
#include <vector>
#include  <utility>

#include "searcher.hpp"
#include "client.hpp"
#include "sorter.hpp"


namespace se{

using Parsed_query = std::pair<std::vector<std::string>, std::vector<std::string>>;

class SearchEngine
{
public:
    explicit SearchEngine(std::shared_ptr<db::Searcher> searcher, std::shared_ptr<Client> client, std::shared_ptr<Sorter> Sorter);
    ~SearchEngine() = default;
    SearchEngine(const SearchEngine&) = delete;
    SearchEngine& operator= (const SearchEngine&) = delete;
    
    void run(size_t length)const;

private:
    Parsed_query createQueriesVectors(const std::vector<std::string>& input)const;

private:
    std::shared_ptr<db::Searcher> m_searcher;
    std::shared_ptr<Client> m_client;
    std::shared_ptr<Sorter> m_sorter;
};

} // namespace se
#endif
