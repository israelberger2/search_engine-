// #include <iostream>
// #include <cstring>
// #include <memory>
// #include <map>
// #include <vector>


// #include "search_engine.hpp"
// #include "indexer.hpp"
// #include "crawler.hpp"
// #include "updater.hpp"
// #include "net_client.hpp"
// #include "se_exceptions.hpp"
// #include "text_client.hpp"
// #include "links_map.hpp"
// #include "configuration.hpp"
// #include "publisher.hpp"
// #include "pageRank.hpp"
// #include "pr_sorter.hpp"
// #include "safe_scores_map.hpp"
// #include "pagerank_scheduler.hpp"
// #include "regular_sorter.hpp"
// #include "link.hpp"
// #include "mysql_links_data.hpp"
// #include "mysql_graph_data.hpp"
// #include "mysql_word_data.hpp"
// #include "mysql_word_links.hpp"
 
// #include "mysql_searcher.hpp"
// #include "mysql_word_data.hpp"
// #include "mysql_searcher.hpp"
// #include "mysql_searcher.hpp"


// using namespace se;

 
// int main(int argc, char* argv[]) 
// {
  
  

  

  

  
  

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

//     RegularSorter sorter{};
//     std::shared_ptr<db::Searcher> mysqlSearcher = std::make_shared<db::MysqlSearcher>();

//     SearchEngine search(mysqlSearcher, indexer, links, *client, sorter);
//     search.handle(Config::getLengthResult());
//     cr.close();
 
//   }catch (const ServerSocketError& error){
//     std::clog << error.what() << "\n";
//     return 1;
//   } catch (...){
//     std::clog << "ERROR:: the Program failed\n";
//     return 1;
//   }
  
//   return 0; 
// }
// ...............................................................

// befor change to pr sort

// #include <iostream>
// #include <cstring>
// #include <memory>
// #include <map>
// #include <vector>
// #include <unordered_map>
// #include <string>


// #include "search_engine.hpp"
// #include "indexer.hpp"
// #include "crawler.hpp"
// #include "updater.hpp"
// #include "net_client.hpp"
// #include "se_exceptions.hpp"
// #include "text_client.hpp"
// #include "links_map.hpp"
// #include "configuration.hpp"
// #include "publisher.hpp"
// #include "pageRank.hpp"
// #include "pr_sorter.hpp"
// #include "safe_scores_map.hpp"
// #include "links_rank_manager.hpp"
// #include "regular_sorter.hpp"
// #include "link.hpp"
// #include "mysql_links_data.hpp"
// #include "mysql_graph_data.hpp"
// #include "mysql_word_data.hpp"
// #include "mysql_word_links.hpp"
 
// #include "mysql_searcher.hpp"
// #include "mysql_word_data.hpp"
// #include "mysql_searcher.hpp"
// #include "mysql_searcher.hpp"
// #include "mysql_links_rank_manager.hpp"


// using namespace se;

 
// int main(int argc, char* argv[]) 
// {
  
//   LinksMap links{}; 
//   Indexer indexer{};
//   SafeScoresPointer scores{};
//   db::MysqlLinksRankManager rankManager(scores);

//   Publisher publisher(rankManager);
//   db::MysqlGraphData graph{};
//   db::MysqlWordLinks wordsLinks{};

//   Updater inserter(publisher, graph, wordsLinks);

//   Crawler cr(inserter);
//   try{
//     cr.crawl();

//     std::unique_ptr<Client> client;
//     if(argc >= 2 &&  !std::strcmp(argv[1], "net")){
//         client = std::make_unique<NetClient>();
//       } else {
//         client = std::make_unique<TextClient>();
//       }

//     RegularSorter sorter{};
//     std::shared_ptr<db::Searcher> mysqlSearcher = std::make_shared<db::MysqlSearcher>();

//     SearchEngine search(mysqlSearcher, *client, sorter);
//     search.run(Config::getLengthResult());
//     cr.close();
 
//   }catch (const SocketError& error){
//     std::clog << error.what() << "\n";
//     return 1;
//   } catch (...){
//     std::clog << "ERROR:: the Program failed" << "\n";
//     return 1;
//   }
  
//   return 0; 
// }


#include <iostream>
#include <cstring>
#include <memory>
#include <map>
#include <vector>
#include <unordered_map>
#include <string>


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
#include "links_rank_manager.hpp"
#include "regular_sorter.hpp"
#include "link.hpp"
#include "mysql_links_data.hpp"
#include "mysql_graph_data.hpp"
#include "mysql_word_data.hpp"
#include "mysql_word_links.hpp"
 
#include "mysql_searcher.hpp"
#include "mysql_word_data.hpp"
#include "mysql_searcher.hpp"
#include "mysql_searcher.hpp"
#include "mysql_links_rank_manager.hpp"
#include "pr_sorter.hpp"
#include "safe_limit_counter.hpp"
#include <thread>


using namespace se;

 
int main(int argc, char* argv[]) 
{
  SafeLimitCounter s(5);
  auto threadFunction = [&s]() {
      for (int i = 0; i < 5; ++i) {
          bool b = s.CheckLimitAndIncrement();
          std::cout << "Thread " << std::this_thread::get_id() << ": bool is " << b << '\n';
        }
    };

    // Create two threads and run them concurrently
    std::thread thread1(threadFunction);
    std::thread thread2(threadFunction);

    // Join threads to the main thread
    thread1.join();
    thread2.join();
  
   
  
  // LinksMap links{}; 
  // Indexer indexer{};
  // SafeScoresPointer scores{};
  // db::MysqlLinksRankManager rankManager(scores);

  // Publisher publisher(rankManager);
  // db::MysqlGraphData graph{};
  // db::MysqlWordLinks wordsLinks{};

  // Updater inserter(publisher, graph, wordsLinks);

  // Crawler cr(inserter);
  // try{
  //   cr.crawl();

  //   std::unique_ptr<Client> client;
  //   if(argc >= 2 &&  !std::strcmp(argv[1], "net")){
  //       client = std::make_unique<NetClient>();
  //     } else {
  //       client = std::make_unique<TextClient>();
  //     }

  //   // RegularSorter sorter{};
  //   PrSorted sorter(scores);
  //   std::shared_ptr<db::Searcher> mysqlSearcher = std::make_shared<db::MysqlSearcher>();

  //   SearchEngine search(mysqlSearcher, *client, sorter);
  //   search.run(Config::getLengthResult());
  //   cr.close();
 
  // }catch (const SocketError& error){
  //   std::clog << error.what() << "\n";
  //   return 1;
  // }catch (const std::out_of_range& error){
  //   std::cout << error.what() << '\n'; 
  // } catch (...){
  //   std::clog << "ERROR:: the Program failed" << "\n";
  //   return 1;
  // }
  
  return 0; 
}
