#ifndef MYSQL_SEARCHER_HPP 
#define MYSQL_SEARCHER_HPP 

#include <vector>
#include <string>
#include <utility>

#include "searcher.hpp"
#include "mysql_word_links.hpp"
#include "mysql_word_data.hpp"

 
namespace db{

using LinksAndCount = std::pair<std::string,int>;
using Links = std::vector<std::string>;

class MysqlSearcher : public Searcher
{
public:
    MysqlSearcher();
    ~MysqlSearcher() = default;
    MysqlSearcher(const MysqlSearcher&) = delete;
    MysqlSearcher& operator= (const MysqlSearcher&) = delete;
   
    std::vector<LinksAndCount> search(const Links& positiveWords, const Links& negativeWords)const override;

private:
    std::pair<int,int> getwordsCountSum(const std::vector<int>& wordsID, const std::string& url)const;
    std::vector<LinksAndCount> checkNegativeWords(const std::vector<int>& wordsID, std::vector<LinksAndCount>& IntermediateResult)const;
    void checkPositiveWords(const std::vector<int>& wordsID, const std::string& url, std::vector<LinksAndCount>& resLinks)const;

private:
    MysqlWordLinks m_wordLinks;
    MysqlWordData m_wordData;
};
 
} //se
#endif

