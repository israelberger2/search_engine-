#include "crawler_injector.hpp"
#include "mysql_links_rank_manager.hpp"
#include "safe_scores_map.hpp"
#include "updater.hpp"
#include "mysql_graph_data.hpp"
#include "mysql_word_links.hpp"
#include "configuration.hpp"
#include "dfs.hpp"
#include "bfs.hpp"
  

namespace se{

std::unique_ptr<Crawler> Crawler_Injector::create()const 
{
    SafeScoresPointer scores{};
    db::MysqlLinksRankManager rankManager(scores);

    Publisher publisher(rankManager);
    db::MysqlGraphData graph{};
    db::MysqlWordLinks wordsLinks{};

    Updater updater(publisher, graph, wordsLinks);

    auto scaner = (Config::getScanType() == "bfs") ?
    std::shared_ptr<SafeScan<std::string>>(std::make_shared<Bfs<std::string>>()) :
    std::shared_ptr<SafeScan<std::string>>(std::make_shared<Dfs<std::string>>());

    return std::make_unique<Crawler>(updater, scaner);
}

}// namespace se