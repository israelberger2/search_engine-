#ifndef LINKS_RANK_MANAGER_HPP 
#define LINKS_RANK_MANAGER_HPP 
  

namespace db{
    
class LinkRankManager
{
public:
    virtual ~LinkRankManager() = 0;
    virtual void update() = 0;

};

} //db
#endif
