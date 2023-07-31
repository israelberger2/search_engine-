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
 

bool fff(const std::vector<int>& wordsID, int linksID)
{
  db::Connector connector{};
  
  std::unique_ptr<sql::Connection> con = connector.get_conector();
  con->setSchema("DBsearchEngine");

  std::string query  = "SELECT COUNT(WordLink.LinkID) FROM WordLink WHERE WordLink.LinkID = ?  and (WordLink.WordID = ? ";
  std::string appendString;
  for(size_t i = 1; i < wordsID.size(); ++i){
    std::string appendString = " OR WordLink.WordID = ?";
    query.append(appendString);
  }
  query.append(")");
   
  std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(query));

  stmt->setInt(1, linksID);
  for(size_t i = 0; i < wordsID.size(); ++i){
    stmt->setInt(i+2, wordsID[i]);
  }

  std::unique_ptr<sql::ResultSet> result(stmt->executeQuery());

  size_t count = 0;
 
  while(result->next()){
    count = result->getInt(1);
  }

  return count == wordsID.size() ? true : false;
}

std::vector<int> check(const std::vector<int>& wordsID, const std::vector<int>& linksID)
{
  if(wordsID.empty() || linksID.empty()){
    return linksID;
  }

  std::vector<int> validLinks;

  for(auto& link : linksID){
    if(fff(wordsID, link)){
      validLinks.push_back(link);
      std::cout << "valid" << '\n';
    } else{
      std::cout << "invalide" << '\n';
    }
  }

  return validLinks;
}

int main(int argc, char* argv[]) 
{
  db::MysqlWordData wordData{};
  std::vector<int> wordsID = wordData.getWordsID(std::vector<std::string>{"Potter", "some", "than" });

  db::MysqlWordLinks wl{};
  std::vector<int> linksID = wl.getLinksForWord("Ball");

  for(auto link : linksID){
    std::cout << "links: " << link << '\n';
    
  }
  std::vector<int> result = check(wordsID, linksID);
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
