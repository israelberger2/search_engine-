#include <algorithm>
 
#include "word_instance_sorter.hpp"

 
void se::WordInstanceSorter::sort_links(std::vector<std::pair<std::string, int>>& linksVector, size_t num_res)const
{           
    if(num_res >= linksVector.size()){
        num_res = linksVector.size();
    }
    
    std::partial_sort(linksVector.begin(), linksVector.begin() + num_res, linksVector.end(), 
        [](const std::pair<std::string, int>& part1, const std::pair<std::string, int>& part2)
        {return part1.second > part2.second;
    }); 
} // namespace s
