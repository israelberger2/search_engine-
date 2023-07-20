#ifndef WORDDATA_HPP 
#define WORDDATA_HPP 

#include <string>

 
namespace db{
 
class WordData
{
public:
    virtual ~WordData() = default;
    virtual int insertAndGetID(const std::string& word) = 0;
};
 
} //db
#endif
