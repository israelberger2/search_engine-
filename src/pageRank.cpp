#include "pageRank.hpp"
#include "mysql_graph_data.hpp"

#include <algorithm>


// namespace se {

// PageRank::PageRank()
// : m_curMap()
// , m_preMap()
// {}

// doubleelMap PageRank::calculate(const LinksMapGet &linkser)
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
//     double outChance = 0.85;
//     double stayChanc = 0.15;

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
//         double degreePage = m_curMap[link.first] / sizeMap;
//         for(auto l : link.second){
//             m_curMap[l.first] += degreePage;
//         }
//     }
// }
#include <iostream>
#include <algorithm>
#include <limits>

#include "pageRank.hpp"
#include "mysql_graph_data.hpp"


namespace se {


PageRank::PageRank()
: m_curMap()
, m_preMap()
{}

DoubleMap PageRank::calculate()
{  
    // db::MysqlGraphData graphData{};
    // std::unordered_map<std::string, std::vector<std::string>> graph = graphData.linkRelationships();
    std::unordered_map<std::string, std::vector<std::string>> graph = {{"A",std::vector<std::string>{"B",}},{"B",std::vector<std::string>{"C"}},{"C",std::vector<std::string>{"D"}},{"D",std::vector<std::string>{"B"}}};
    size_t sizeMap = graph.size();
    std::cout << "sizedatais " << sizeMap << '\n';
    
    
    std::unordered_map<std::string, double> preMap;
    preMap.reserve(sizeMap);
    
    for(auto& g : graph){
        preMap.insert({g.first, 1});
    }
    
    double difference = std::numeric_limits<double>::max();  
    std::cout << "mmmmmm" << difference << '\n';
;
    int counter = 0;
    
    
    while(counter++ <= 61){
        // std::cout << "i is: " << counter << '\n';
        
        std::unordered_map<std::string, double> currentMap;
        // std::cout << "size is: " << preMap.size() << '\n';
        
        currentMap.reserve(preMap.size());
        
        for(auto p : preMap){
            currentMap.insert({p.first, 0});
        }

        for(auto& src : graph){
            double degreePage = preMap[src.first] / src.second.size();
            for(auto& destination : src.second){
                currentMap[destination] += degreePage;
            }
        }
        
        double outChance = 0.85;
        double stayChanc = 0.15;
        int totalLinks = preMap.size();

        for(auto& page : currentMap){
            page.second *= outChance;
            page.second += (stayChanc / totalLinks);  
        }

        double curDifference = 0;
        for(auto c : currentMap){
            curDifference += c.second;
        } 
         
        std::cout << "curDifference: " <<  curDifference << "\n";
        std::cout << "Difference: " <<  difference << "\n";
        if(difference - curDifference < 0.0001 ){ //fill the condition
            std::cout << "iteration is: " << counter << '\n';
            for(auto e : currentMap){
                std::cout << "link is: " << e.first << ".  grade is: " << e.second<< '\n';
            }
            return currentMap;
        }

        difference = curDifference;
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
//     double outChance = 0.85;
//     double stayChanc = 0.15;

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

// void PageRank::calculator( std::unordered_map<std::string, double>& links)
// {   
//     size_t sizeMap = links.size();

//     for(auto link : links){
//         double degreePage = m_curMap[link.first] / sizeMap;
//         for(auto l : link.second){
//             m_curMap[l.first] += degreePage;
//         }
//     }
// }

} // namespace s
