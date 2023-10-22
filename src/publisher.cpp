#include "publisher.hpp"
 

se::Publisher::Publisher(db::LinkRankManager& linkRankManager)
: m_coordinator(linkRankManager)
{}

void se::Publisher::notify()
{
    m_coordinator.update();
}
