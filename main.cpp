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
#include "mysql_searcher.hpp"
#include "mysql_word_data.hpp"


using namespace se;

 
int main(int argc, char* argv[]) 
{
  
   db::MysqlWordData word{};
  int res = word.insertAndGetID("aaaaasccccccssssssssssaaaaaaaaaaaaaaaBall");
   std::cout << "id of Baal: " << res << '\n';
  

  
  // MysqlSearcher searcher{};
  // auto res = searcher.search(std::vector<std::string>{ "report"}, std::vector<std::string>{"Potter"});
  // std::cout << "res: " << res.size() << "\n";
  
   

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
