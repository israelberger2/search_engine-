#ifndef SORTER_HPP
#define SORTER_HPP

#include <string>
#include <vector>
#include <utility>


namespace se{

class Sorter
{
public:
    virtual ~Sorter() = default;
    virtual void sort_links(std::vector<std::pair<std::string, int>>& linksVector, size_t num_res)const = 0;
};

} // namespace se
#endif
