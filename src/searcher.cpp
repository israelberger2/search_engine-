#include <memory>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "searcher.hpp"
#include "connector.hpp"


se::Searcher::Searcher(db::WordLinks& wordLinks, db::WordData& wordData)
: m_wordLinks(wordLinks)
, m_wordData(wordData)
{}

std::vector<se::WordsInstance> se::Searcher::search(const std::vector<std::string>& positiveWords, const std::vector<std::string>& negativeWords)const
{
  if(positiveWords.empty()){
    return std::vector<WordsInstance>{};
  }

   std::vector<std::string> links = m_wordLinks.getLinksForWord(positiveWords[0]);

   std::vector<int> wordsID = m_wordData.getWordsID(positiveWords);

  if(links.empty() || wordsID.size() < positiveWords.size()){
    return std::vector<WordsInstance>{};
  }

  std::vector<WordsInstance> IntermediateResult;

  for(auto& link : links){
    checkPositiveWords(wordsID, link, IntermediateResult);
  }
  
  if(IntermediateResult.empty()){
    return std::vector<WordsInstance>{};
  }

  std::vector<int> negativewordsID = m_wordData.getWordsID(negativeWords);

  std::vector<std::pair<std::string, int>> result = checkNegativeWords(negativewordsID, IntermediateResult);

  return result;
}

std::pair<size_t,int> se::Searcher::sumAndCountOfwordInLink(const std::vector<int>& wordsID, const std::string& url)const
{
  db::Connector connector{};
  std::unique_ptr<sql::Connection> con = connector.get_conector();
  con->setSchema("DBsearchEngine");

  std::string query  = "SELECT COUNT(WordLink.LinkID), SUM(WordLink.Count) FROM Link JOIN WordLink ON"
  " Link.ID = WordLink.LinkID WHERE Link.Address = ? and (WordLink.WordID = ? ";
  std::string appendString;
  
  for(size_t i = 1; i < wordsID.size(); ++i){        
    std::string appendString = " OR WordLink.WordID = ?";
    query.append(appendString);
  }
  query.append(")");
    
  std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(query));

  stmt->setString(1, url);
  for(size_t i = 0; i < wordsID.size(); ++i){
    stmt->setInt(i+2, wordsID[i]);
  }
   
  std::unique_ptr<sql::ResultSet> result(stmt->executeQuery());

  size_t count = 0;
  int sum;

  while(result->next()){        
    count = result->getInt(1);
    sum = result->getInt(2);
  }

  return std::pair<size_t,int>{count,sum};
}

void se::Searcher::checkPositiveWords(const std::vector<int>& wordsID, const std::string& url, std::vector<WordsInstance>& resLinks)const
{
  if(wordsID.empty()){
    return;
  }

  std::pair<size_t,int> result = sumAndCountOfwordInLink(wordsID, url);
  
  if(result.first == wordsID.size()){      
    resLinks.push_back({url,result.second});
  }
}

std::vector<se::WordsInstance> se::Searcher::checkNegativeWords(const std::vector<int>& wordsID, std::vector<WordsInstance>& IntermediateResult)const
{
  if(wordsID.empty()){
    return IntermediateResult;
  }

  std::vector<WordsInstance> result;

  for(auto& pair : IntermediateResult){
    std::pair<size_t, int> res = sumAndCountOfwordInLink(wordsID, pair.first);
    if(res.first == 0){
      result.push_back({pair.first, pair.second});
    }
  }
   
  return result;
}