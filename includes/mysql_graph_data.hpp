#ifndef MYSQL_GRAPH_HPP 
#define MYSQL_GRAPH_HPP 

#include <unordered_map>
 
#include "graph_data.hpp"
 

namespace db{

using Map = std::unordered_map<std::string, int>;

class MysqlGraphData : public GraphData
{
public:
    MysqlGraphData();
    ~MysqlGraphData() = default;
    MysqlGraphData(const MysqlGraphData&) = delete;
    MysqlGraphData& operator= (const MysqlGraphData&) = delete;

    void insert(const Map& destinations, const std::string& src)const override;
    Graph linkRelationships()const override; 
    std::vector<int> linkRelated(int linkID)const;
};
 
} //db
#endif
