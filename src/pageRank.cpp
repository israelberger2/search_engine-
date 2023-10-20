#include "pageRank.hpp"
#include "mysql_graph_data.hpp"

#include <algorithm>


// namespace se {

// PageRank::PageRank()
// : m_curMap()
// , m_preMap()
// {}

// FloatelMap PageRank::calculate(const LinksMapGet &linkser)
// {    
//     std::unordered_map<std::string, IntMap> links = linkser.get_map();
//     size_t sizeMap = linkser.size();

//     std::unordered_map<std::string, IntMap> specificMap;
//     specificMap.reserve(sizeMap);
//     std::vector<std::string> keys;  
    
//     for(auto link : links){
//         keys.push_back(link.first);
//     }

//     for(auto key : links){
//         for(auto value : key.second){
//             auto end = keys.end();
//             auto res = std::find(keys.begin(), end ,value.first);
//             if(res != end){
//                 specificMap.insert(value);
//             }
//         }
//     }

//     initMaps(specificMap, sizeMap);

//     int counter = 0;
     
//     while(counter++ <= 51){
        
//         restartMaps();
//         calculator(specificMap);
//         DampingFactor_calculate(sizeMap);
//     }    
    
//     return m_curMap;
// }

// void PageRank::initMaps(std::unordered_map<std::string, IntMap>& links, size_t sizeMap)
// {
//     m_curMap.reserve(sizeMap);
//     m_preMap.reserve(sizeMap);
    
//     for(auto link : links){
//         m_curMap.insert({link.first, 0});
//         m_preMap.insert({link.first, 1});
//     }
// }

// void PageRank::DampingFactor_calculate(size_t totalLinks)
// {
//     float outChance = 0.85;
//     float stayChanc = 0.15;

//     for(auto page : m_curMap){
//         page.second *= outChance;
//         page.second += (stayChanc / totalLinks);
//     }
// }

// void PageRank::restartMaps()
// {
//     m_curMap.swap(m_preMap);
//     for(auto item : m_curMap){
//         item.second = 0;
//     }
// }

// void PageRank::calculator(std::unordered_map<std::string, IntMap>& links)
// {   
//     size_t sizeMap = links.size();

//     for(auto link : links){
//         float degreePage = m_curMap[link.first] / sizeMap;
//         for(auto l : link.second){
//             m_curMap[l.first] += degreePage;
//         }
//     }
// }
#include <iostream>
#include "pageRank.hpp"
#include "mysql_graph_data.hpp"

#include <algorithm>

namespace se {


PageRank::PageRank()
: m_curMap()
, m_preMap()
{}

FloatelMap PageRank::calculate()
{  
    db::MysqlGraphData graphData{};
    std::unordered_map<std::string, std::vector<std::string>> graph = graphData.linkRelationships();
    
    size_t sizeMap = graph.size();
    std::cout << "sizedatais " << sizeMap << '\n';
    
    
    std::unordered_map<std::string, float> preMap;
    preMap.reserve(sizeMap);
    
    for(auto& g : graph){
        preMap.insert({g.first, 1});
    }
    

    int counter = 0;
    while(counter++ <= 61){
        std::cout << "i is: " << counter << '\n';
        
        std::unordered_map<std::string, float> currentMap;
        std::cout << "size is: " << preMap.size() << '\n';
        
        currentMap.reserve(preMap.size());
        
        for(auto p : preMap){
            currentMap.insert({p.first, 0});
        }

        for(auto& src : graph){
            float degreePage = preMap[src.first] / src.second.size();
            for(auto& destination : src.second){
                currentMap[destination] += degreePage;
            }
        }
        
        float outChance = 0.85;
        float stayChanc = 0.15;
        int totalLinks = preMap.size();

        for(auto& page : currentMap){
            page.second *= outChance;
            page.second += (stayChanc / totalLinks);// this is the first theorem of pagerank
        }

        float res = 0;
        for(auto c : currentMap){
            res+= c.second;
        } 
        std::cout << "res: " << res << '\n';
        

        if(1 > 2){ //fill the condition
            return currentMap;
        }

        preMap = currentMap;
        //comper between currentMAp and preMap if not equal or aproxmition then updete that preMap = CurrentMap
        // and itarete again   
    }

    return preMap;
}

// void PageRank::initMaps(std::unordered_map<std::string, IntMap>& links, size_t sizeMap)
// {
//     m_curMap.reserve(sizeMap);
//     m_preMap.reserve(sizeMap);
    
//     for(auto link : links){
//         m_curMap.insert({link.first, 0});
//         m_preMap.insert({link.first, 1});
//     }
// }

// void PageRank::DampingFactor_calculate(size_t totalLinks)
// {
//     float outChance = 0.85;
//     float stayChanc = 0.15;

//     for(auto page : m_curMap){
//         page.second *= outChance;
//         page.second += (stayChanc / totalLinks);
//     }
// }

// void PageRank::restartMaps()
// {
//     m_curMap.swap(m_preMap);
//     for(auto item : m_curMap){
//         item.second = 0;
//     }
// }

// void PageRank::calculator( std::unordered_map<std::string, float>& links)
// {   
//     size_t sizeMap = links.size();

//     for(auto link : links){
//         float degreePage = m_curMap[link.first] / sizeMap;
//         for(auto l : link.second){
//             m_curMap[l.first] += degreePage;
//         }
//     }
// }

} // namespace s
