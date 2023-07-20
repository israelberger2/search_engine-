#ifndef PAGERANK_SCHEDULER_HPP 
#define PAGERANK_SCHEDULER_HPP 

#include "safe_scores_map.hpp"
#include "links_map_get.hpp"


namespace se{
    
class PagerankScheduler
{
public:
    PagerankScheduler(SafeScoresPointer& scoresMap, LinksMapGet& linksMap);
    ~PagerankScheduler() = default;
    PagerankScheduler(const PagerankScheduler&) = default;
    PagerankScheduler& operator= (const PagerankScheduler&) = default;

    void update();

private:
    LinksMapGet& m_linksMap;
    SafeScoresPointer& m_scoresMap;
};

} //se
#endif
