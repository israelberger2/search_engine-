#include <limits>
#include "pageRank.hpp"


namespace se {

PageRank::PageRank(const Graph& graph)
: m_graph(graph)
, m_preMap()
{
   initPreMap();
}

void PageRank::initPreMap()
{
    m_preMap.reserve(m_graph.size());
    
    for(auto& g : m_graph){
        m_preMap.insert({g.first, 1});
    }
}

DoubleMap PageRank::getScores()
{  
    double gradesSum = std::numeric_limits<double>::max();  
    
    int counter = 0;
    while(counter++ <= 50){
        DoubleMap currentMap = createDoubleMap();
        calculate(currentMap);

        double curGradesSum = 0;
        for(auto c : currentMap){
            curGradesSum += c.second;
        } 
         
        if(gradesSum - curGradesSum < 0.0001 ){
            return currentMap;
        }

        gradesSum = curGradesSum;
        m_preMap = currentMap;
    }

    return m_preMap;
}

DoubleMap PageRank::createDoubleMap()const
{
    DoubleMap map;
    map.reserve(m_preMap.size());
    
    for(auto& p : m_preMap){
        map.insert({p.first, 0});
    }

    return map;
}

void PageRank::calculate(DoubleMap& currentMap)
{
    for(auto& src : m_graph){
        double degreePage = m_preMap[src.first] / src.second.size();
        for(auto& destination : src.second){
            currentMap[destination] += degreePage;
        }
    }
            
    double outChance = 0.85;
    double stayChanc = 0.15;
    int totalLinks = m_preMap.size();

    for(auto& page : currentMap){
        page.second *= outChance;
        page.second += (stayChanc / totalLinks);  
    }
}
 
} // namespace s
