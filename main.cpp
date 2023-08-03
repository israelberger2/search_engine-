#include <iostream>
#include <cstring>
#include <memory>
#include <map>
#include <vector>


#include "search_engine.hpp"
#include "indexer.hpp"
#include "crawler.hpp"
#include "updater.hpp"
#include "net_client.hpp"
#include "se_exceptions.hpp"
#include "text_client.hpp"
#include "links_map.hpp"
#include "configuration.hpp"
#include "publisher.hpp"
#include "pageRank.hpp"
#include "pr_sorter.hpp"
#include "safe_scores_map.hpp"
#include "pagerank_scheduler.hpp"
#include "regular_sorter.hpp"
#include "link.hpp"
#include "mysql_links_data.hpp"
#include "mysql_graph_data.hpp"
#include "mysql_word_data.hpp"
#include "mysql_word_links.hpp"
#include "connector.hpp"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <utility>
#include "searcher.hpp"


using namespace se;

std::pair<size_t,int> sendQuery(const std::vector<int>& wordsID, const std::string& url)
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

void exist(const std::vector<int>& wordsID, const std::string& url, std::vector<std::pair<std::string,int>>& resLinks)
{
  if(wordsID.empty()){
    return;
  }

  std::pair<size_t,int> result = sendQuery(wordsID, url);
  
  if(result.first == wordsID.size()){      
    resLinks.push_back({url,result.second});
  }
}

std::vector<std::pair<std::string,int>> checkNegativeWords(const std::vector<int>& wordsID, std::vector<std::pair<std::string,int>>& IntermediateResult)
{
  if(wordsID.empty()){
    return IntermediateResult;
  }

  std::vector<std::pair<std::string,int>> result;

  for(auto& pair : IntermediateResult){
    std::pair<size_t, int> res = sendQuery(wordsID, pair.first);
    if(res.first == 0){
      result.push_back({pair.first, pair.second});
    }
  }
   
  return result;
}


std::vector<std::pair<std::string,int>> find(const std::vector<std::string>& positiveWords, const std::vector<std::string>& negativeWords)
{
  if(positiveWords.empty()){
    return std::vector<std::pair<std::string,int>>{};
  }

  db::MysqlWordLinks wordlinks{};
  std::vector<std::string> links = wordlinks.getLinksForWord(positiveWords[0]);

  db::MysqlWordData wordData{};
  std::vector<int> wordsID = wordData.getWordsID(positiveWords);

  if(links.empty() || wordsID.size() < positiveWords.size()){
    return std::vector<std::pair<std::string,int>>{};
  }

  std::vector<std::pair<std::string,int>> IntermediateResult;

  for(auto& link : links){
    exist(wordsID, link, IntermediateResult);
  }
  
  if(IntermediateResult.empty()){
    return std::vector<std::pair<std::string,int>>{};
  }

  std::vector<int> negativewordsID = wordData.getWordsID(negativeWords);

  std::vector<std::pair<std::string, int>> result = checkNegativeWords(negativewordsID, IntermediateResult);

  return result;
}


int main(int argc, char* argv[]) 
{
  db::MysqlWordLinks wordLinks{};
  db::MysqlWordData wordData{};

  Searcher searcher(wordLinks, wordData);
  auto res = searcher.search(std::vector<std::string>{ "report"}, std::vector<std::string>{"Potter"});
  std::cout << "res: " << res.size() << "\n";
  // std::vector<std::string> query = {"Ball"};
  //  std::vector<std::string> negative = {"Potter"};
  // std::vector<std::pair<std::string,int>> result = find(query,negative);

  // std::cout << "size of result: " << result.size() << '\n';
  
  // for(auto& res : result){
  //   std::cout << "link: " << res.first << "  instance: " << res.second << '\n';
    
  // }

   


  // for(auto r : result){
  //   std::cout << "link:  " << r.first << "  instance: " << r.second << '\n';
  // }

  // std::vector<std::string> positive = {"Harry", "Potter"};
  // std::vector<std::string> negative = {"Ballddddddd", "Ball", "DSss"};
  // std::cout << "size of negative: " << negative.size() << '\n';
  // for(auto n : negative){
  //   std::cout << "ne:  " << n << '\n';
    
  // }
  
    
   
  // std::vector<int> result = check(positive, negative);
  // std::cout << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << '\n';
  
  // for(auto res : result){
  //   std::cout << "id: " << res << '\n';
    
  //}
   



//   LinksMap links{}; 
//   Indexer indexer{};
//   SafeScoresPointer scores{};
//   PageRank pagerank;
//   PagerankScheduler scheduler(scores, links);
//   Publisher publisher(scheduler);
//   db::MysqlGraphData graph{};
//   db::MysqlWordLinks wordsLinks{};

//   Updater inserter(3, publisher, graph, wordsLinks);

//   Crawler cr(inserter);
//   try{
//     cr.crawl();

//     std::unique_ptr<Client> client;
//     if(argc >= 2 &&  !std::strcmp(argv[1], "net")){
//         client = std::make_unique<NetClient>();
//       } else {
//         client = std::make_unique<TextClient>();
//       }

//     PrSorted sorter(scores);
//     SearchEngine search(indexer, links, *client, sorter);
//     search.handle(Config::getLengthResult());
//     cr.close();
 
//   }catch (const ServerSocketError& error){
//     std::clog << error.what() << "\n";
//     return 1;
//   } catch (...){
//     std::clog << "ERROR:: the Program failed\n";
//     return 1;
//   }
  
  return 0; 
}
