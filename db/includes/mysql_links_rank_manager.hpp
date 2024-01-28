#ifndef SQL_LINKS_RANK_MANAGER_HPP 
#define SQL_LINKS_RANK_MANAGER_HPP 

#include "links_rank_manager.hpp"
#include "safe_scores_map.hpp"
 

namespace db{
    
class MysqlLinksRankManager : public LinkRankManager 
{
public:
    MysqlLinksRankManager(se::SafeScoresPointer& scoresMap);
    ~MysqlLinksRankManager() = default;
    MysqlLinksRankManager(const MysqlLinksRankManager&) = default;
    MysqlLinksRankManager& operator= (const MysqlLinksRankManager&) = default;

    void update()override;

private:
    se::SafeScoresPointer& m_scoresMap;
};

} //db
#endif
