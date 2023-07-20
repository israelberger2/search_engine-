#ifndef WORDLINKS_HPP
#define WORDLINKS_HPP

#include <string>
#include <unordered_map>


namespace db
{

using WordsMap = std::unordered_map<std::string, int>;
    
class WordLinks 
{
public:
    virtual ~WordLinks() = default;
    virtual void insert(const WordsMap& words, const std::string& link) = 0;
};

} // db
#endif



