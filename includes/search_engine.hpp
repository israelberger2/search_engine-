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
    explicit SearchEngine(std::shared_ptr<db::Searcher> searcher, std::shared_ptr<Client> client, std::shared_ptr<Isorter> sorter);
    ~SearchEngine() = default;
    SearchEngine(const SearchEngine&) = delete;
    SearchEngine& operator= (const SearchEngine&) = delete;
    
    void run(size_t length)const;
    bool createQueriesVectors(std::vector<std::string>& positive, std::vector<std::string>& negative, const std::vector<std::string>& input)const;

private:
    std::shared_ptr<db::Searcher> m_searcher;
    std::shared_ptr<Client> m_client;
    std::shared_ptr<Isorter> m_arranger;
};

} // namespace se
#endif
