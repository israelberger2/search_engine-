#ifndef MYSQL_GRAPH_HPP 
#define MYSQL_GRAPH_HPP 

#include <unordered_map>
#include <utility>
 
#include "graph_data.hpp"
#include "safe_unordered_map.hpp"


namespace db{

using Map = std::unordered_map<std::string, int>;

class MysqlGraph : public GraphData
{
public:
    MysqlGraph();
    ~MysqlGraph() = default;
    MysqlGraph(const MysqlGraph&) = delete;
    MysqlGraph& operator= (const MysqlGraph&) = delete;

    void insert(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const;
    void insert(const Map& destinations, const std::string& src)const override;
    Graph getLinkRelationships()const override; 
    
private:
    std::vector<int> RelatedLinksID(int linkID)const; 
    std::pair<std::string, std::vector<std::string>> getRelatedLinks(int linkID)const;
    std::string createJsonPages(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const;
};
 
} //db
#endif
