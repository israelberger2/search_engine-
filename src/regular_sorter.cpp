#include <algorithm>
 
#include "regular_sorter.hpp"

 
void se::RegularSorter::sort_links(std::vector<std::pair<std::string, size_t>>& linksVector, size_t num_res)const
{       
    if(linksVector.empty()){
        return;
    }

    std::partial_sort(linksVector.begin(), linksVector.begin() + num_res, linksVector.end(), 
        [](const std::pair<std::string, size_t>& part1, const std::pair<std::string, size_t>& part2)
        {return part1.second > part2.second;
    }); 
} // namespace s
