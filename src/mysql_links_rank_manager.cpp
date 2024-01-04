#include <unordered_map>
#include <string>
#include <iostream>

#include "mysql_links_rank_manager.hpp"
#include "mysql_graph_data.hpp"
#include "pageRank.hpp"
#include "se_exceptions.hpp"


db::MysqlLinksRankManager::MysqlLinksRankManager(se::SafeScoresPointer& scoresMap)
: m_scoresMap(scoresMap)
{}

void db::MysqlLinksRankManager::update()
{
    try{
        MysqlGraphData graphData{};
        auto graph = graphData.linkRelationships();

        se::PageRank pagerank{graph};
        auto scoreMam = pagerank.getScores();
        std::cout << "befor pagerank" << '\n';
        
        m_scoresMap.updateScores(scoreMam);
        std::cout << "after pagerank" << '\n';
        
    }catch(const se::NoGraph& e){
        std::clog << e.what() << '\n';
    }
}
