#ifndef LINKS_RANK_MANAGER_HPP 
#define LINKS_RANK_MANAGER_HPP 
          
#include "subscriber.hpp"
#include "safe_scores_map.hpp"
#include "publisher.hpp"


namespace db{
    
class LinksRankManager : public se::Subscriber 
{
public:
    LinksRankManager(se::SafeScoresPointer& scoresMap, se::Publisher& publisher);
    ~LinksRankManager() = default;
    LinksRankManager(const LinksRankManager&) = default;
    LinksRankManager& operator= (const LinksRankManager&) = default;

    void update()override;
    void unsubscribe()override;

private:
    se::SafeScoresPointer& m_scoresMap;
    se::Publisher& m_publisher;
};

} //db
#endif
