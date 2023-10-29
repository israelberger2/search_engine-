#ifndef PAGERANk_HPP
#define PAGERANk_HPP

#include <unordered_map>
#include <vector>
#include <string>

 
namespace se{

using Graph = std::unordered_map<std::string, std::vector<std::string>>;
using DoubleMap = std::unordered_map<std::string, double>;
 
class PageRank
{
public:
    explicit PageRank(const Graph& graph);
    ~PageRank() = default;
    PageRank(const PageRank&) = default;
    PageRank& operator= (const PageRank&) = default;

    DoubleMap getScores();
 
private:
    void calculate(DoubleMap& currentMap);
    void initPreMap();
    DoubleMap createDoubleMap()const;

private:
    Graph m_graph;
    DoubleMap m_preMap;
};

} // namespace se
#endif
