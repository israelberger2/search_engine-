#include <iostream>

#include "links_rank_manager.hpp"
#include "mysql_graph_data.hpp"
#include "pageRank.hpp"
#include "se_exceptions.hpp"

 
db::LinksRankManager::LinksRankManager(se::SafeScoresPointer& scoresMap, se::Publisher& publisher)
: m_scoresMap(scoresMap)
, m_publisher(publisher)
{
    publisher.add(this);
}

void db::LinksRankManager::update()
{    
    try{
        MysqlGraph graphData{};
        auto graph = graphData.getLinkRelationships();

        se::PageRank pagerank{graph};
        auto scoreMam = pagerank.getScores();
            
        m_scoresMap.updateScores(scoreMam);        
    }catch(const se::NoGraph& e){
        std::clog << e.what() << '\n';
    }
}

void db::LinksRankManager::unsubscribe()
{
    m_publisher.remove(this);
}
