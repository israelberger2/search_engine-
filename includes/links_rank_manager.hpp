#ifndef LINKS_RANK_MANAGER_HPP 
#define LINKS_RANK_MANAGER_HPP 
  

namespace db{
    
class LinkRankManager
{
public:
    virtual ~LinkRankManager() = default;
    virtual void update() = 0;

};

} //db
#endif
