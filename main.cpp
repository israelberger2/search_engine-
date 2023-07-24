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

std::vector<int> get_wordsID(const std::vector<std::string>& querys)
{
  if(querys.empty()){
    return std::vector<int>{};
  }

  db::Connector connector{};
  std::unique_ptr<sql::Connection> con = connector.get_conector();
  con->setSchema("DBsearchEngine");
   
  std::string query = "SELECT ID FROM Word WHERE TOKEN = ? ";
  size_t size = 0;
  
  while(size++ < querys.size()-1){
    std::string supplementary = " OR Token = ?";
    query += supplementary;
  }
  
  std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(query));
  
  for(size_t i  = 0; i < querys.size(); ++i){
    stmt->setString(i+1, querys[i]);
  }
  

  std::unique_ptr<sql::ResultSet> linkResultes(stmt->executeQuery());

  std::vector<int> result;
  while(linkResultes->next()){
    result.push_back(linkResultes->getInt("id"));
  }

  return result;
}

int main(int argc, char* argv[]) 
{
  db::MysqlWordData w{};
  std::vector<int> res = w.getWordsID(std::vector<std::string>{"Harry", "Potter", "Ball", "ygyugygyuyg"});
  for(auto r : res){
    std::cout << "id: " << r << '\n';
    
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
