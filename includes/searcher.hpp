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
#include <utility>

#include "word_links.hpp"
#include "word_data.hpp"

 
namespace se{

using WordsInstance = std::pair<std::string,int>;

class Searcher
{
public:
    Searcher(db::WordLinks& wordLinks, db::WordData& wordData);
    ~Searcher() = default;
    Searcher(const Searcher&) = default;
    Searcher& operator= (const Searcher&) = default;
   
    std::vector<WordsInstance> search(const std::vector<std::string>& positiveWords, const std::vector<std::string>& negativeWords)const;

private:
    std::pair<size_t,int> sumAndCountOfwordInLink(const std::vector<int>& wordsID, const std::string& url)const;
    std::vector<WordsInstance> checkNegativeWords(const std::vector<int>& wordsID, std::vector<WordsInstance>& IntermediateResult)const;
    void checkPositiveWords(const std::vector<int>& wordsID, const std::string& url, std::vector<WordsInstance>& resLinks)const;

private:
    db::WordLinks& m_wordLinks;
    db::WordData& m_wordData;
};
 
} //se
#endif

