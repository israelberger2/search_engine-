#ifndef MYSQL_GRAPH_HPP 
#define MYSQL_GRAPH_HPP 

#include <utility>
#include <vector>

#include "graph_data.hpp"
#include "connector.hpp"
#include "link.hpp" 


namespace db{

using Map = std::unordered_map<std::string, int>;

class MysqlGraphData : public GraphData
{
public:
    MysqlGraphData();
    ~MysqlGraphData() = default;
    MysqlGraphData(const MysqlGraphData&) = delete;
    MysqlGraphData& operator= (const MysqlGraphData&) = delete;

    void insert(const std::pair<std::string, int>& destin, int srcID)override; 
    void insert(const Map& destinations, const std::string& src)override;

private:
    Connector m_connector;
};
 
} //db
#endif

#ifndef MYSQL_GRAPH_HPP 
#define MYSQL_GRAPH_HPP 

#include <utility>
#include <vector>
#include<string> 

#include "graph_data.hpp"
#include "connector.hpp"


namespace db{
 
class MysqlGraphData : public GraphData
{
public:
    MysqlGraphData();
    ~MysqlGraphData() = default;
    MysqlGraphData(const MysqlGraphData&) = delete;
    MysqlGraphData& operator= (const MysqlGraphData&) = delete;

    void insert(const std::pair<std::string, int>& link, int sourceID)override; 
    void insert(const std::pair<std::string, int>& link, const std::string& source)override;

private:
    Connector m_connector;
};
 
} //db
#endif

