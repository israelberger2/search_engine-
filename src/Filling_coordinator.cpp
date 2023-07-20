#include "Filling_coordinator.hpp"

se::FillingCoordinator::FillingCoordinator(IndexerInsertion &indexer, LinksMamInsertion &linksMap, Pagerank &pagerank, size_t mount)
: m_inexer(indexer)
, m_waiterIndexer()
, m_linkMap(linksMap)
, m_waiterLinksMap()
, m_pagerank(pagerank)
, m_fillTriger()
, m_mount(mount)
{}

void se::FillingCoordinator::bringResCrewl(std::pair<std::vector<std::string>, std::string> &resCrewl)
{
    m_waiterIndexer.insert(resCrewl.second);
    m_waiterLinksMap.insert(resCrewl.first);
    ++m_fillTriger;

    if(m_fillTriger == m_mount){
        m_linkMap = m_waiterLinksMap;
        m_pagerank.restart()
    }
}
