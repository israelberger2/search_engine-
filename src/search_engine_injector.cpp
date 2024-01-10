#include "search_engine_injector.hpp"
#include "pr_sorter.hpp"
#include "mysql_searcher.hpp"
#include "configuration.hpp"
#include "net_client.hpp"
#include "text_client.hpp"


namespace se
{

SearchEngine_injector::SearchEngine_injector()
: m_client(nullptr)
, m_sorter(nullptr)
{}

std::shared_ptr<SearchEngine> SearchEngine_injector::create(SafeScoresPointer& scores) 
{
    m_client = (Config::getClientType() == "net") ? 
        std::shared_ptr<Client>(std::make_unique<NetClient>()) : 
        std::shared_ptr<Client>(std::make_unique<TextClient>());
    
    auto sorter = std::make_shared<PrSorter>(scores);
    m_sorter = sorter;
    
    auto mysqlSearcher = std::make_shared<db::MysqlSearcher>();

 
    auto search_engine = std::make_shared<SearchEngine>(mysqlSearcher, *m_client, m_sorter);
    // search_engine->run(10);
    return search_engine;
}
      
} // namespace se

  