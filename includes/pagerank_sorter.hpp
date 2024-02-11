#ifndef PR_SORTED_HPP
#define PR_SORTED_HPP

#include <string>
#include <vector>
#include <utility>

#include "sorter.hpp"
#include "safe_scores_map.hpp"


namespace se{

class PageRankSorter : public Isorter
{
public:
    explicit PageRankSorter(const SafeScoresPointer& score);
    ~PageRankSorter() = default;
    PageRankSorter(const PageRankSorter&) = default;
    PageRankSorter& operator= (const PageRankSorter&) = default;

    void sort_links(std::vector<std::pair<std::string, int>>& linksVector, size_t num_res)const override;

private:
    const SafeScoresPointer& m_score;
};

} // namespace se
#endif
