// #include <iostream>
// #include <algorithm>
// #include <utility>

// #include "pageRank.hpp"


// namespace se {

// PageRank::PageRank(LinksMapGet &linkser)
// : m_linkser(linkser)
// , m_scorePages()     
// {}

// void PageRank::calculate()
// {    
//     std::unordered_map<std::string, float> currentScore;
//     std::unordered_map<std::string, float> lastScore;
//     std::unordered_map<std::string, IntMap> links = m_linkser.get_map();
//     size_t sizeMap = m_linkser.size();

//     initMaps(currentScore, lastScore, links, sizeMap);

//     int counter = 0;
     
//     while(counter++ <= 51){
        
//         restartMaps(currentScore, lastScore);
//         calculator(links, currentScore);
//         DampingFactor_calculate(currentScore, sizeMap);
//     }    
//     m_scorePages = currentScore;
// }

// void PageRank::initMaps(FloatelMap& currentMap, FloatelMap& lastMap, const std::unordered_map<std::string, IntMap>& links, size_t sizeMap)const
// {
//     currentMap.reserve(sizeMap);
//     lastMap.reserve(sizeMap);
    
//     for(auto link : links){
//         currentMap.insert({link.first, 0});
//         lastMap.insert({link.first, 1});
//     }
// }

// void PageRank::DampingFactor_calculate(FloatelMap& map, size_t totalLinks)
// {
//     float outChance = 0.85;
//     float stayChanc = 0.15;

//     for(auto page : map){
//         page.second *= outChance;
//         page.second += (stayChanc / totalLinks);
//     }
// }

// bool PageRank::scoreIsConvergent(FloatelMap &currentScore, FloatelMap &lastScore) const
// {    
//     std::vector<std::pair<std::string, float>> scoreVector(currentScore.begin(), currentScore.end());

//     std::sort(scoreVector.begin(), scoreVector.end(), [](const auto& p1, const auto& p2) {
//         return p1.second > p2.second;
//     });

//     std::vector<std::pair<std::string, float>> scoreVector2(lastScore.begin(), lastScore.end());
//     std::sort(scoreVector2.begin(), scoreVector2.end(), [](const auto& p1, const auto& p2) {
//         return p1.second > p2.second;
//     });
 
//     auto it = scoreVector.begin();
//     auto it2 = scoreVector2.begin();
//     auto itEnd = scoreVector.end();
//     while(it != itEnd){
//         if(it->first != it2->first){
//             return false;
//         }
//         ++it;
//         ++it2;
//     }
        
//     return true;
// }

// void PageRank::restartMaps(FloatelMap& currentMap,FloatelMap& lastMap)const
// {
//     currentMap.swap(lastMap);
//     for(auto item : currentMap){
//         item.second = 0;
//     }
// }

// void PageRank::calculator(std::unordered_map<std::string, IntMap>& links, FloatelMap& currentScore)const
// {   
//     size_t sizeMap = links.size();

//     for(auto item : links){
//         float degreePage = currentScore[item.first] / sizeMap;
//         for(auto it : item.second){
//             currentScore[it.first] += degreePage;
//         }
//     }
// }

// void PageRank::update()
// {
//     calculate();
// }

// FloatelMap PageRank::get_scorePages()const
// {    
//     return m_scorePages;
// }

// } // namespace s


#include "pageRank.hpp"
#include <algorithm>


namespace se {

PageRank::PageRank()
: m_curMap()
, m_preMap()
{}

FloatelMap PageRank::calculate(const LinksMapGet &linkser)
{    
    std::unordered_map<std::string, IntMap> links = linkser.get_map();
    size_t sizeMap = linkser.size();

    std::unordered_map<std::string, IntMap> specificMap;
    specificMap.reserve(sizeMap);
    std::vector<std::string> keys;  
    for(auto link : links){
        keys.push_back(link.first);
    }

    for(auto key : links){
        for(auto value : key.second){
            auto end = keys.end();
            auto res = std::find(keys.begin(), end ,value.first);
            if(res != end){
                specificMap.insert(value);
            }
        }
    }

    initMaps(specificMap, sizeMap);

    int counter = 0;
     
    while(counter++ <= 51){
        
        restartMaps();
        calculator(specificMap);
        DampingFactor_calculate(sizeMap);
    }    
    return m_curMap;
}

void PageRank::initMaps(std::unordered_map<std::string, IntMap>& links, size_t sizeMap)
{
    m_curMap.reserve(sizeMap);
    m_preMap.reserve(sizeMap);
    
    for(auto link : links){
        m_curMap.insert({link.first, 0});
        m_preMap.insert({link.first, 1});
    }
}

void PageRank::DampingFactor_calculate(size_t totalLinks)
{
    float outChance = 0.85;
    float stayChanc = 0.15;

    for(auto page : m_curMap){
        page.second *= outChance;
        page.second += (stayChanc / totalLinks);
    }
}

void PageRank::restartMaps()
{
    m_curMap.swap(m_preMap);
    for(auto item : m_curMap){
        item.second = 0;
    }
}

void PageRank::calculator(std::unordered_map<std::string, IntMap>& links)
{   
    size_t sizeMap = links.size();

    for(auto item : links){
        float degreePage = m_curMap[item.first] / sizeMap;
        for(auto it : item.second){
            m_curMap[it.first] += degreePage;
        }
    }
}

} // namespace s
