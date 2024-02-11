#ifndef LINKSDATA_HPP 
#define LINKSDATA_HPP 

#include <string>


namespace db{
 
class LinksData
{
public:
    virtual ~LinksData() = default;

    virtual int insertAndGetLinkID(const std::string& link)const = 0;
    virtual std::string getLink(int id)const = 0;
    virtual std::vector<std::string> getLinks(std::vector<int> linksID)const = 0;
};
 
} //db
#endif

