// #ifndef LINKSDATA_HPP 
// #define LINKSDATA_HPP 

// #include "link.hpp"


// namespace db{
 
// class LinksData
// {
// public:
//     virtual ~LinksData() = default;
//     virtual int insertAndGetLinkID(const se::Link& link)const = 0;
// };
 
// } //db
// #endif


#ifndef LINKSDATA_HPP 
#define LINKSDATA_HPP 

#include <string>


namespace db{
 
class LinksData
{
public:
    virtual ~LinksData() = default;
    virtual int insertAndGetLinkID(const std::string& link)const = 0;
};
 
} //db
#endif

