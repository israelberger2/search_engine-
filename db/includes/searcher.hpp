#ifndef SEARCHER_HPP 
#define SEARCHER_HPP 

#include <vector>
#include <string>
#include <utility>

 
namespace db{

class Searcher 
{
public:
    virtual ~Searcher() = default;
    virtual std::vector<std::pair<std::string,int>> search(const std::vector<std::string>& positiveWords, const std::vector<std::string>& negativeWords)const = 0;
};

}// namespace se
#endif