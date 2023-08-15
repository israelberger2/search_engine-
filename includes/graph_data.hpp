#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <string>
#include <unordered_map>


namespace db{

using Map = std::unordered_map<std::string, int>;

class GraphData
{
public:
    virtual ~GraphData() = default;
    virtual void insert(const Map& destinations, const std::string& src)const = 0;
};
 
} //db
#endif
