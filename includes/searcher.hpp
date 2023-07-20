#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <vector>
#include <string>
#include  <utility>


namespace se{

class Searcher
{
public:
    virtual ~Searcher() = default;
    
    virtual std::vector<std::pair<std::string, size_t>> get_links(const std::vector<std::string>& querie)const = 0;
};

} // namespace se
#endif
