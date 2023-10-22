#include <unordered_map>
#include <string>

#include "mysql_links_rank_manager.hpp"
#include "mysql_graph_data.hpp"
#include "pageRank.hpp"


db::MysqlLinksRankManager::MysqlLinksRankManager(se::SafeScoresPointer& scoresMap)
: m_scoresMap(scoresMap)
{}

void db::MysqlLinksRankManager::update()
{
    MysqlGraphData graphData{};
    auto graph = graphData.linkRelationships();

    se::PageRank pagerank{graph};
    auto scoreMam = pagerank.getScores();
    
    m_scoresMap.updateScores(scoreMam);
}
