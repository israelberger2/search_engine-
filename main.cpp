#include <iostream>
 
#include "search_engine.hpp"
#include "crawler.hpp"
#include "se_exceptions.hpp"
#include "crawler_injector.hpp"
#include "search_engine_injector.hpp"
#include "safe_scores_map.hpp"
#include "configuration.hpp"

using namespace se;
  

int main() 
{    
  try{
    SafeScoresPointer scores{};

    Crawler_Injector crawler_injector(scores);
    auto crawler = crawler_injector.create();
    crawler.crawl();

    auto search_engine = searchEngine_injector(scores);  
    search_engine.run(Config::getLengthResult());    
    crawler.close();
  
    return 0; 
  }catch (const SocketError& error){
    std::clog << error.what() << "\n";
    return 1;
  }catch (const std::out_of_range& error){
    std::cout << error.what() << '\n'; 
  } catch (...){
    std::clog << "ERROR:: the Program failed" << "\n";
    return 1;
  }
}
