#ifndef publisher_HPP
#define publisher_HPP

#include "links_rank_manager.hpp"


namespace se{

class Publisher
{
public:
    explicit Publisher(db::LinkRankManager& linkRankManager);
    ~Publisher() = default;
    Publisher(const Publisher&) = default;
    Publisher& operator= (const Publisher&) = default;

    void notify();

private:
    db::LinkRankManager& m_coordinator;
};

} // namespace se
#endif
