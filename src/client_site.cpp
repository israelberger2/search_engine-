#include <vector>
#include <string>
#include  <utility>
#include <iostream>
#include <iostream>
  
#include "client_site.hpp"
#include "se_excaptions.hpp"


namespace se{
  
ClientSite::ClientSite(Searcher& searcher, TextClient& tui)
: m_searcher(searcher)
, m_tui(tui)
{}
 
void ClientSite::run()const
{
  while(true){
    std::vector<std::string> keywords = m_tui.load_query();

    std::vector<std::pair<std::string, size_t>> links;

    try{
      links = m_searcher.get_links(keywords);
    } catch(const NetworkError& net){
      std::cout << net.what();
    }
    try{ 
      m_tui.send_data(links);
    } catch(const DataError& jError) {
      continue;
    } catch (const NetworkError& error){
      std::cout << error.what();
    }
  }
}

} // namespace se

