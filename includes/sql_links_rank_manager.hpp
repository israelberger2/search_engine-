#ifndef SQL_LINKS_RANK_MANAGER_HPP 
#define SQL_LINKS_RANK_MANAGER_HPP 

#include "links_rank_manager.hpp"
#include "safe_scores_map.hpp"
 

namespace db{
    
class SqlLinksRankManager : public LinkRankManager 
{
public:
    SqlLinksRankManager(se::SafeScoresPointer& scoresMap);
    ~SqlLinksRankManager() = default;
    SqlLinksRankManager(const SqlLinksRankManager&) = default;
    SqlLinksRankManager& operator= (const SqlLinksRankManager&) = default;

    void update()override;

private:
    se::SafeScoresPointer& m_scoresMap;
};

} //db
#endif
