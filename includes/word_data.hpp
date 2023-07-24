#ifndef WORDDATA_HPP 
#define WORDDATA_HPP 

#include <vector>
#include <string>

 
namespace db{
 
class WordData
{
public:
    virtual ~WordData() = default;
    virtual int insertAndGetID(const std::string& word) = 0;
    virtual std::vector<int> getWordsID(const std::vector<std::string>& queries) = 0;
};
 
} //db
#endif
