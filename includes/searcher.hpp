// #ifndef SEARCHER_HPP
// #define SEARCHER_HPP

// #include <vector>
// #include <string>
// #include  <utility>


// namespace se{

// class Searcher
// {
// public:
//     virtual ~Searcher() = default;
    
//     virtual std::vector<std::pair<std::string, size_t>> get_links(const std::vector<std::string>& querie)const = 0;
// };

// } // namespace se
// #endif

#ifndef SEARCHER_HPP 
#define SEARCHER_HPP 

#include <vector>
#include <string>

#include "word_data.hpp"
#include "links_data.hpp"

 
namespace se{
 
class Searcher
{
public:
    Searcher(db::WordData& wordData, db::LinksData& linkData);
    ~Searcher() = default;
    Searcher(const Searcher&) = default;
    Searcher& operator= (const Searcher&) = default;

    std::vector<int> search(const std::vector<std::string>& positiveWords, const std::vector<std::string>& negativeWords)const;

private:
    bool validLink(const std::vector<int>& wordsID, int linksID, bool existingWordsSearch);

private:
    db::WordData& m_wordData;
    db::LinksData& m_linkData;
};
 
} //se
#endif

