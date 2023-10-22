#include <unordered_map>
#include <string>

#include "sql_links_rank_manager.hpp"
#include "mysql_graph_data.hpp"
#include "pageRank.hpp"


db::SqlLinksRankManager::SqlLinksRankManager(se::SafeScoresPointer& scoresMap)
: m_scoresMap(scoresMap)
{}

void db::SqlLinksRankManager::update()
{
    MysqlGraphData graphData{};
    std::unordered_map<std::string, std::vector<std::string>> graph = graphData.linkRelationships();
    se::PageRank pagerank{graph};
    std::unordered_map<std::string, double> scoreMam = pagerank.getScores();
    m_scoresMap.updateScores(scoreMam);
}
