#ifndef SEARCH_ENGINE_INJECTOR_HPP 
#define SEARCH_ENGINE_INJECTOR_HPP 

#include<memory>
#include "search_engine.hpp"
#include "safe_scores_map.hpp"
#include "pr_sorter.hpp"

 
namespace se{
 
class SearchEngine_injector
{
public:
    SearchEngine_injector();
    ~SearchEngine_injector() = default;
    SearchEngine_injector(const SearchEngine_injector&) = delete;
    SearchEngine_injector& operator= (const SearchEngine_injector&) = delete;

    std::shared_ptr<SearchEngine> create(SafeScoresPointer& scores);

private:
    std::shared_ptr<Client> m_client;
    std::shared_ptr<PrSorter> m_sorter;
};
 
} //se
#endif
