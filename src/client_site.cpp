#include <vector>
#include <string>
#include  <utility>
#include <iostream>
   
#include "client_site.hpp"
#include "se_exceptions.hpp"
#include "network_handler.hpp"


namespace se{
  
ClientSite::ClientSite(TextClient& tui)
: m_tui(tui)
{}
 
void ClientSite::run()const
{
   
  while(true){     
    std::vector<std::string> keywords = m_tui.load_query();     
    std::vector<std::pair<std::string, int>> links;

    // try{
      NetworkHandler m_searcher{};
       
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
  }
}

} // namespace se
