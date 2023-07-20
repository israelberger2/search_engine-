#include <unordered_map>
#include <string>

#include "pagerank_scheduler.hpp"
#include "pageRank.hpp"


se::PagerankScheduler::PagerankScheduler(SafeScoresPointer &scoresMap, LinksMapGet &linksMap)
: m_linksMap(linksMap)
, m_scoresMap(scoresMap)
{}

void se::PagerankScheduler::update()
{
    PageRank pagerank{};
    std::unordered_map<std::string, float> scoreMam = pagerank.calculate(m_linksMap);
    m_scoresMap.updateScores(scoreMam);
}
