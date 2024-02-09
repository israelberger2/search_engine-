#include "crawler_injector.hpp"
#include "configuration.hpp"
#include "dfs.hpp"
#include "bfs.hpp"
  

namespace se{
 
Crawler_Injector::Crawler_Injector(SafeScoresPointer& scores)
: m_rankManager(scores)
, m_publisher(m_rankManager)
, m_graph()
, m_wordLinks()
, m_updater(m_publisher, m_graph, m_wordLinks)
{}

Crawler Crawler_Injector::create() 
{
    auto scaner = (Config::getScanType() == "bfs") ?
    std::shared_ptr<SafeScaner<std::string>>(std::make_shared<Bfs<std::string>>()) :
    std::shared_ptr<SafeScaner<std::string>>(std::make_shared<Dfs<std::string>>());

    return Crawler(m_updater, scaner);
}

}// namespace se