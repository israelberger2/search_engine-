#include <iostream>
#include <cstring>
#include <memory>

#include "search_engine.hpp"
#include "crawler.hpp"
#include "updater.hpp"
#include "net_client.hpp"
#include "se_exceptions.hpp"
#include "text_client.hpp"
#include "publisher.hpp"
#include "pageRank.hpp"
#include "pr_sorter.hpp"
#include "links_rank_manager.hpp"
#include "regular_sorter.hpp"
#include "mysql_links_data.hpp"
#include "mysql_graph_data.hpp"
 
#include "mysql_searcher.hpp"
#include "mysql_links_rank_manager.hpp"
#include "pr_sorter.hpp"
#include "safe_limit_counter.hpp"
#include <thread>
#include "configuration.hpp"
#include "se_exceptions.hpp"


using namespace se;
  
int main(int argc, char* argv[]) 
{ 
  // Indexer indexer{};
  SafeScoresPointer scores{};
  db::MysqlLinksRankManager rankManager(scores);

  Publisher publisher(rankManager);
  db::MysqlGraphData graph{};
  db::MysqlWordLinks wordsLinks{};

  Updater inserter(publisher, graph, wordsLinks);

  Crawler cr(inserter);
  try{
    cr.crawl();

    std::unique_ptr<Client> client;
    if(argc >= 2 &&  !std::strcmp(argv[1], "net")){
        client = std::make_unique<NetClient>();
      } else {
        client = std::make_unique<TextClient>();
      }

    PrSorted sorter(scores);
    std::shared_ptr<db::Searcher> mysqlSearcher = std::make_shared<db::MysqlSearcher>();

    SearchEngine search(mysqlSearcher, *client, sorter);
    search.run(Config::getLengthResult());
    cr.close();
 
  }catch (const SocketError& error){
    std::clog << error.what() << "\n";
    return 1;
  }catch (const std::out_of_range& error){
    std::cout << error.what() << '\n'; 
  } catch (...){
    std::clog << "ERROR:: the Program failed" << "\n";
    return 1;
  }
  
  return 0; 
}
