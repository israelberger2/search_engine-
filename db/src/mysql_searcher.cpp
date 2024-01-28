#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

#include "mysql_searcher.hpp"
#include "connector.hpp"
#include <iostream>


db::MysqlSearcher::MysqlSearcher()
: m_wordLinks()
, m_wordData()
{}

std::vector<db::WordsInstance> db::MysqlSearcher::search(const Links& positiveWords, const Links& negativeWords)const
{
  std::vector<std::pair<std::string, int>> result;

  try{
    if(positiveWords.empty()){
      return std::vector<WordsInstance>{};
    }

    Links links = m_wordLinks.getLinksForWord(positiveWords[0]);
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

    result = checkNegativeWords(negativewordsID, IntermediateResult); 
  } catch(const sql::SQLException& e){
    std::clog << "searcher: " << e.what() << '\n';
  }

  return result;
}

std::pair<int,int> db::MysqlSearcher::sumAndCountOfwordInLink(const std::vector<int>& wordsID, const std::string& url)const
{  
  std::string query  = "SELECT COUNT(WordLink.LinkID), SUM(WordLink.Count) FROM Link JOIN WordLink ON"
  " Link.ID = WordLink.LinkID WHERE Link.Address = ? and (WordLink.WordID = ? ";
  
  for(size_t i = 1; i < wordsID.size(); ++i){        
    std::string appendString = " OR WordLink.WordID = ?";
    query.append(appendString);
  }
  query.append(")");
  
  db::Connector connector{};
  std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

  stmt->setString(1, url);
  for(size_t i = 0; i < wordsID.size(); ++i){
    stmt->setInt(i+2, wordsID[i]);
  }

  int count = 0;
  int sum = 0;

  try{
    std::unique_ptr<sql::ResultSet> result(stmt->executeQuery());
  
    while(result->next()){        
      count = result->getInt(1);
      sum = result->getInt(2);
    }
  }catch(const sql::SQLException& e){
    std::clog << "error from MysqlSearcher::sumAndCountOfwordInLink: " << e.what() << '\n';
  }

  return std::pair<int,int>{count,sum};
}

void db::MysqlSearcher::checkPositiveWords(const std::vector<int>& wordsID, const std::string& url, std::vector<WordsInstance>& resLinks)const
{
  std::pair<size_t,int> result = sumAndCountOfwordInLink(wordsID, url);
  
  if(result.first == wordsID.size()){      
    resLinks.push_back({url,result.second});
  }
}

std::vector<db::WordsInstance> db::MysqlSearcher::checkNegativeWords(const std::vector<int>& wordsID, std::vector<WordsInstance>& IntermediateResult)const
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