#include <algorithm>
#include <memory>
 
#include "pagerank_sorter.hpp"
 
 
namespace se{

PageRankSorter::PageRankSorter(const SafeScoresPointer& score)
: m_score(score)
{}

void PageRankSorter::sort_links(std::vector<std::pair<std::string, int>>& linksVector, size_t num_res)const
{            
    if(linksVector.empty()){
        return;
    }
    
    if(num_res >= linksVector.size()){
        num_res = linksVector.size() -1;
    }

    std::shared_ptr<std::unordered_map<std::string, double>> scores = m_score.getScores();
    
    if (!scores) {        
        std::partial_sort(linksVector.begin(), linksVector.begin() + num_res, linksVector.end());      
    } else{        
        std::partial_sort(linksVector.begin(), linksVector.begin() + num_res, linksVector.end(),
            [&scores](const std::pair<std::string, int>& part1, const std::pair<std::string, int>& part2){
                return (static_cast<double>(part1.second) * scores->at(part1.first)) >
                (static_cast<double>(part2.second) * scores->at(part2.first));
            }
        ); 
    }    
}
 
} // namespace se
 