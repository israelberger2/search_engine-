#include <vector>
#include <string>
#include <iostream>
   
#include "client_site.hpp"
#include "se_exceptions.hpp"
#include "network_handler.hpp"


namespace se{
  
ClientSite::ClientSite()
: m_tui()
{}
 
void ClientSite::run() 
{
  while(true){     
    try{
      std::vector<std::string> keywords = m_tui.load_query();     
 
      NetworkHandler m_searcher{};       
      auto links = m_searcher.get_links(keywords);
      m_tui.send_data(links);
    }catch(const DataError& e) {
      std::clog << "ClientSite::run " << e.what() << '\n';
    }catch (const NetworkError& e){
      std::clog << "ERROR::404 page not found " << '\n';
      break;
    }catch(const Exit& e){
      break;
    }catch(const SocketError& e){
      std::clog << "ClientSite::run " << e.what() << '\n';
      break;
    }
  }
}

} // namespace se
