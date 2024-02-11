#ifndef REGULAR_SORT_HPP 
#define REGULAR_SORT_HPP 

#include <string>
#include <vector>
#include <utility>

#include "sorter.hpp"
 

namespace se
{

class WordInstanceSorter : public Isorter
{
public:
    WordInstanceSorter() = default;
    ~WordInstanceSorter() = default;
    WordInstanceSorter(const WordInstanceSorter&) = default;
    WordInstanceSorter& operator= (const WordInstanceSorter&) = default;

    void sort_links(std::vector<std::pair<std::string, int>>& linksVector, size_t num_res)const override;
};

} //se
#endif
