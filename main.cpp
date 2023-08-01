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


using namespace se;
 

bool exist(const std::vector<int>& wordsID, int linksID, bool existingWordsSearch)
{
  db::Connector connector{};
  
  std::unique_ptr<sql::Connection> con = connector.get_conector();
  con->setSchema("DBsearchEngine");

  std::string query  = "SELECT COUNT(WordLink.LinkID) FROM WordLink WHERE WordLink.LinkID = ?  and (WordLink.WordID = ? ";
  std::string appendString;
  for(size_t i = 1; i < wordsID.size(); ++i){ 
    std::cout << "iteration" << '\n';
       
    std::string appendString = " OR WordLink.WordID = ?";
    query.append(appendString);
  }
  query.append(")");
   
  std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(query));

  stmt->setInt(1, linksID);
  for(size_t i = 0; i < wordsID.size(); ++i){
    std::cout << "set iteration" << '\n';
    
    stmt->setInt(i+2, wordsID[i]);
  }
  std::cout << "befor result(stmt->executeQuery());" << '\n';
  
  std::unique_ptr<sql::ResultSet> result(stmt->executeQuery());

  size_t count = 0;
  std::cout << "befor result" << '\n';
 
  while(result->next()){
    std::cout << "result->next" << '\n';
    
    count = result->getInt(1);
  }
  
  if(existingWordsSearch){
    return count == wordsID.size() ? true : false;
  }

  return !count ? true : false;
}

// std::vector<int> check(const std::vector<int>& positiveWords, const std::vector<int>& negativeWords, const std::vector<int>& linksID)
// {
//   if(positiveWords.empty() || linksID.empty()){
//     return linksID;
//   }

//   std::vector<int> linksContainWords;

//   for(auto link : linksID){
//     if(exist(positiveWords, link, true)){
//       linksContainWords.push_back(link);
//     }  
//   }

//   std::vector<int> result;

//   for(auto link : linksContainWords){
//     if(exist(negativeWords, link, false)){
//       result.push_back(link);
//     }
//   }

//   return result;
// }
 
 std::vector<int> check(const std::vector<std::string>& positiveWords, const std::vector<std::string>& negativeWords)
{
  db::MysqlWordData wordData{};
  db::MysqlWordLinks wordlinks{};
  std::vector<int> linksID = wordlinks.getLinksForWord(positiveWords[0]);
  
  std::vector<int> linksContainWords;
  
  if(positiveWords.size() > 1){
    std::vector<int> wordsID = wordData.getWordsID(std::vector<std::string>{positiveWords.begin()+1, positiveWords.end()});
    
    if(wordsID.size() < positiveWords.size()-1){
      return std::vector<int>{};
    }

    for(auto link : linksID){
      if(exist(wordsID, link, true)){
        linksContainWords.push_back(link);
      }  
    }
  } else{
    linksContainWords = linksID;
  }

  std::vector<int> result;
  std::vector<int> negativeWordsID = wordData.getWordsID(negativeWords);
  if(negativeWordsID.empty()){
    return linksContainWords;
  } 
 
  for(auto link : linksContainWords){
    if(exist(negativeWordsID, link, false)){
      result.push_back(link);
    }
  }

  return result;
}


int main(int argc, char* argv[]) 
{
  std::vector<std::string> positive = {"Harry", "Potter"};
  std::vector<std::string> negative = {"Ballddddddd", "Ball", "DSss"};
  std::cout << "size of negative: " << negative.size() << '\n';
  for(auto n : negative){
    std::cout << "ne:  " << n << '\n';
    
  }
  
    
   
  std::vector<int> result = check(positive, negative);
  std::cout << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << '\n';
  
  for(auto res : result){
    std::cout << "id: " << res << '\n';
    
  }
   



  // LinksMap links{}; 
  // Indexer indexer{};
  // SafeScoresPointer scores{};
  // PageRank pagerank;
  // PagerankScheduler scheduler(scores, links);
  // Publisher publisher(scheduler);
  // db::MysqlGraphData graph{};
  // db::MysqlWordLinks wordsLinks{};

  // Updater inserter(3, publisher, graph, wordsLinks);

  // Crawler cr(inserter);
  // try{
  //   cr.crawl();

  //   std::unique_ptr<Client> client;
  //   if(argc >= 2 &&  !std::strcmp(argv[1], "net")){
  //       client = std::make_unique<NetClient>();
  //     } else {
  //       client = std::make_unique<TextClient>();
  //     }

  //   PrSorted sorter(scores);
  //   SearchEngine search(indexer, links, *client, sorter);
  //   search.handle(Config::getLengthResult());
  //   cr.close();
 
  // }catch (const ServerSocketError& error){
  //   std::clog << error.what() << "\n";
  //   return 1;
  // } catch (...){
  //   std::clog << "ERROR:: the Program failed\n";
  //   return 1;
  // }
  
  return 0;
}
