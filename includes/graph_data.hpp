#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <string>
#include <unordered_map>
#include <vector>

#include "safe_unordered_map.hpp"


namespace db{

using Map = std::unordered_map<std::string, int>;
using Graph = std::unordered_map<std::string, std::vector<std::string>>;

class GraphData
{
public:
    virtual ~GraphData() = default;
    virtual void insert(const Map& destinations, const std::string& src)const = 0;
    virtual void insert(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const = 0;
    virtual Graph linkRelationships()const =0; 
};
 
} //db
#endif
