#ifndef WORDLINKS_HPP
#define WORDLINKS_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include "safe_unordered_map.hpp"


namespace db
{

using Map = std::unordered_map<std::string, int>;
    
class WordLinks 
{
public:
    virtual ~WordLinks() = default;

    virtual void insert(const Map& words, const std::string& link)const = 0;
    virtual void insert(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const = 0;
    virtual std::vector<std::string> getLinksContainingWord(const std::string& word)const = 0;
};

} // db
#endif



