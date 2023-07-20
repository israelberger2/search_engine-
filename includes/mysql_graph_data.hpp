#ifndef MYSQL_GRAPH_HPP 
#define MYSQL_GRAPH_HPP 

#include <unordered_map>
 
#include "graph_data.hpp"
#include "connector.hpp"
 

namespace db{

using Map = std::unordered_map<std::string, int>;

class MysqlGraphData : public GraphData
{
public:
    MysqlGraphData();
    ~MysqlGraphData() = default;
    MysqlGraphData(const MysqlGraphData&) = delete;
    MysqlGraphData& operator= (const MysqlGraphData&) = delete;

    void insert(const Map& destinations, const std::string& src)override;

private:
    Connector m_connector;
};
 
} //db
#endif
