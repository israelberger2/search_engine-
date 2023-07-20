// #ifndef PAGERANH_HPP
// #define PAGERANH_HPP

// #include <unordered_map>
// #include <string>

// #include "links_map_get.hpp"


// namespace se{

// using FloatelMap = std::unordered_map<std::string, float>;
// using IntMap = std::unordered_map<std::string, size_t>;

// class PageRank
// {
// public:
    
//     explicit PageRank(LinksMapGet& linkser);
//     ~PageRank() = default;
//     PageRank(const PageRank&) = default;
//     PageRank& operator= (const PageRank&) = default;

//     void calculate();
//     void calculator(std::unordered_map<std::string, IntMap>& links, FloatelMap& currentScore)const;
//     void update();
//     FloatelMap get_scorePages()const;

// private:
//     void DampingFactor_calculate(FloatelMap& map, size_t totalLinks);
//     bool scoreIsConvergent(FloatelMap& currentScore, FloatelMap& lastScore)const;
//     void restartMaps(FloatelMap& currentMap, FloatelMap& lastMap)const;
//     void initMaps(FloatelMap& currentMap, FloatelMap& lastMap, const std::unordered_map<std::string, IntMap>& links, size_t sizeMap)const;

// private:
//     LinksMapGet& m_linkser;
//     std::unordered_map<std::string, float> m_scorePages;
// };

// } // namespace se
// #endif
#ifndef PAGERANH_HPP
#define PAGERANH_HPP

#include <unordered_map>
#include <string>

#include "links_map_get.hpp"


namespace se{

using FloatelMap = std::unordered_map<std::string, float>;
using IntMap = std::unordered_map<std::string, size_t>;

class PageRank
{
public:
    
    PageRank();
    ~PageRank() = default;
    PageRank(const PageRank&) = default;
    PageRank& operator= (const PageRank&) = default;

    FloatelMap calculate(const LinksMapGet &linkser);
    void calculator(std::unordered_map<std::string, IntMap>& links);
 
private:
    void DampingFactor_calculate(size_t totalLinks);
    void restartMaps();
    void initMaps(std::unordered_map<std::string, IntMap>& links, size_t sizeMap);

private:
    FloatelMap m_curMap;
    FloatelMap m_preMap;
};

} // namespace se
#endif
