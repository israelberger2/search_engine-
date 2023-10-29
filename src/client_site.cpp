// #include <vector>
// #include <string>
// #include  <utility>
// #include <iostream>
// #include <iostream>
  
// #include "client_site.hpp"
// #include "se_exceptions.hpp"


// namespace se{
  
// ClientSite::ClientSite(ProxySearcher& searcher, TextClient& tui)
// : m_searcher(searcher)
// , m_tui(tui)
// {}
 
// void ClientSite::run()const
// {
//   std::cout << "run" << '\n';
  
//   while(true){
//     std::vector<std::string> keywords = m_tui.load_query();
//     std::cout << "beginning load_quary" << '\n';
    
//     std::vector<std::pair<std::string, int>> links;

//     try{
//       links = m_searcher.get_links(keywords);
//     } catch(const NetworkError& net){
//       std::cout << "NetworkErrortttttttttt" << '\n';
      
//       std::cout << net.what();
//     }
    
//     try{ 
//       m_tui.send_data(links);
//     } catch(const DataError& jError) {
//       continue;
//     } catch (const NetworkError& error){
//       std::cout << "in run function error " << error.what();
//     }
//   }
// }

// } // namespace se

#include <vector>
#include <string>
#include  <utility>
#include <iostream>
#include <iostream>
  
#include "client_site.hpp"
#include "se_exceptions.hpp"
#include "proxy_searcher.hpp"


namespace se{
  
ClientSite::ClientSite(TextClient& tui)
: m_tui(tui)
{}
 
void ClientSite::run()const
{
  std::cout << "run" << '\n';
  
  while(true){
    std::cout << "beginnig while.................................................................." << '\n';
    
    std::vector<std::string> keywords = m_tui.load_query();
    std::cout << "beginning load_quary" << '\n';
    
    std::vector<std::pair<std::string, int>> links;

    // try{
      ProxySearcher m_searcher{};
      std::cout << "befor get links" << '\n';
      
      links = m_searcher.get_links(keywords);
    // } catch(const NetworkError& net){
    //   std::cout << "NetworkErrortttttttttt" << '\n';
      
    //   std::cout << net.what() << "\n";
    // }
    
    try{ 
      m_tui.send_data(links);
    } catch(const DataError& jError) {
      continue;
    } catch (const NetworkError& error){
      std::cout << "in run function error " << error.what();
    }
    std::cout << "end of itaretion..................." << '\n';
    
  }
}

} // namespace se
