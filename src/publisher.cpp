#include "publisher.hpp"
 
 
// se::Publisher::Publisher(PageRank& pagerank)
// : m_pagerank(pagerank)   
// {}

// void se::Publisher::notify()
// {
//     m_pagerank.update();
// }

se::Publisher::Publisher(PagerankScheduler& scheduler)
: m_scheduler(scheduler)
{}

void se::Publisher::notify()
{
    m_scheduler.update();
}
