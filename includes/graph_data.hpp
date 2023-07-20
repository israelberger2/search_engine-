// #ifndef GRAPH_HPP 
// #define GRAPH_HPP 

// #include <vector>
// #include <utility>

// #include "link.hpp"


// namespace db{
 
// class GraphData
// {
// public:
//     virtual ~GraphData() = default;

//     virtual void insert(const std::pair<se::Link, int>& link, int sourceID) = 0; 
//     virtual void insert(const std::pair<se::Link, int>& link, const se::Link &source) = 0;
// };
 
// } //db
// #endif


#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <vector>
#include <utility>
#include <string>


namespace db{

using Map = std::unordered_map<std::string, int>;

class GraphData
{
public:
    virtual ~GraphData() = default;

    virtual void insert(const std::pair<std::string, int>& destin, int srcID) = 0; 
    virtual void insert(const Map& destinations, const std::string& src) = 0;
    
};
 
} //db
#endif
