#ifndef MYSQL_SEARCHER_HPP 
#define MYSQL_SEARCHER_HPP 

#include <vector>
#include <string>
#include <utility>

#include "searcher.hpp"
#include "mysql_word_links.hpp"
#include "mysql_word_data.hpp"

 
namespace se{

using WordsInstance = std::pair<std::string,int>;
using Links = std::vector<std::string>;

class MysqlSearcher : public Searcher
{
public:
    MysqlSearcher();
    ~MysqlSearcher() = default;
    MysqlSearcher(const MysqlSearcher&) = delete;
    MysqlSearcher& operator= (const MysqlSearcher&) = delete;
   
    std::vector<WordsInstance> search(const Links& positiveWords, const Links& negativeWords)const override;

private:
    std::pair<int,int> sumAndCountOfwordInLink(const std::vector<int>& wordsID, const std::string& url)const;
    std::vector<WordsInstance> checkNegativeWords(const std::vector<int>& wordsID, std::vector<WordsInstance>& IntermediateResult)const;
    void checkPositiveWords(const std::vector<int>& wordsID, const std::string& url, std::vector<WordsInstance>& resLinks)const;

private:
    db::MysqlWordLinks m_wordLinks;
    db::MysqlWordData m_wordData;
};
 
} //se
#endif

