// #ifndef SORTED_HPP
// #define SORTED_HPP

// #include <string>
// #include <vector>
// #include <utility>

// #include "sorter.hpp"
// #include "pageRank.hpp"


// namespace se{

// class PrSorted : public Isorter
// {
// public:
//     explicit PrSorted(PageRank& pr);
//     ~PrSorted() = default;
//     PrSorted(const PrSorted&) = default;
//     PrSorted& operator= (const PrSorted&) = default;

//     void sort_links(std::vector<std::pair<std::string, size_t>>& linksVector, size_t num_res)const override;

// private:
//     PageRank& m_pagerank;
// };

// } // namespace se
// #endif
#ifndef SORTED_HPP
#define SORTED_HPP

#include <string>
#include <vector>
#include <utility>

#include "sorter.hpp"
#include "safe_scores_map.hpp"


namespace se{

class PrSorted : public Isorter
{
public:
    explicit PrSorted(const SafeScoresPointer& score);
    ~PrSorted() = default;
    PrSorted(const PrSorted&) = default;
    PrSorted& operator= (const PrSorted&) = default;

    void sort_links(std::vector<std::pair<std::string, size_t>>& linksVector, size_t num_res)const override;

private:
    const SafeScoresPointer& m_score;
};

} // namespace se
#endif
