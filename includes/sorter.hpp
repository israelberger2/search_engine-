#ifndef SORTER_HPP
#define SORTER_HPP

#include <string>
#include <vector>
#include <utility>


namespace se{

class Isorter
{
public:
    virtual ~Isorter() = default;
    virtual void sort_links(std::vector<std::pair<std::string, size_t>>& linksVector, size_t num_res)const = 0;
};

} // namespace se
#endif
