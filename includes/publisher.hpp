#ifndef publisher_HPP
#define publisher_HPP

#include "pageRank.hpp"
#include "pagerank_scheduler.hpp"


namespace se{

class Publisher
{
public:
    //explicit Publisher(PageRank& pagerank);
    explicit Publisher(PagerankScheduler& scheduler);
    ~Publisher() = default;
    Publisher(const Publisher&) = default;
    Publisher& operator= (const Publisher&) = default;

    void notify();

private:
    PagerankScheduler& m_scheduler;
};

} // namespace se
#endif
