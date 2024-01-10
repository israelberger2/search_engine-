#include "search_engine_injector.hpp"
#include "pr_sorter.hpp"
#include "regular_sorter.hpp"
#include "mysql_searcher.hpp"
#include "configuration.hpp"
#include "net_client.hpp"
#include "text_client.hpp"


namespace se
{

SearchEngine searchEngine_injector(SafeScoresPointer& scores) 
{
    auto client = (Config::getClientType() == "net") ? 
        std::shared_ptr<Client>(std::make_shared<NetClient>()): 
        std::shared_ptr<Client>(std::make_shared<TextClient>());
    
    auto sorter = (Config::getSortType() == "pageRank") ?
        std::shared_ptr<Isorter>(std::make_shared<PrSorter>(scores)):
        std::shared_ptr<Isorter>(std::make_shared<RegularSorter>());

    auto mysql_searcher = std::make_shared<db::MysqlSearcher>();

    return SearchEngine(mysql_searcher, client, sorter); 
}
  
} // namespace se