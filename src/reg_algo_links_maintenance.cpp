#include <algorithm>
 
#include "reg_algo_links_maintenance.hpp"


namespace se{

RegularAlgo_LinksMaintenance::RegularAlgo_LinksMaintenance()
: m_links()
{}

void RegularAlgo_LinksMaintenance::setListLinks(std::vector<std::string>& links)
{
  m_links = links;
}

void RegularAlgo_LinksMaintenance::remove_invalid_links()
{
  auto result_remove_if =  std::remove_if(m_links.begin(), m_links.end(), 
  [&](const std::string& link){return (link  == "#" || link == "/f");});

  m_links.erase(result_remove_if, m_links.end()); 
}

void RegularAlgo_LinksMaintenance::fixLinks(const std::string& baseURL)
{
  remove_invalid_links();

  for(auto& link : m_links){
    if (link.find("://") != std::string::npos){
      continue;
    }
  
    std::string tmp = baseURL;
    
    if (link[0] == '/'){
      std::string::size_type pos = baseURL.find("/", 8);
      if (pos != std::string::npos){
        tmp  = baseURL.substr(0, pos);
      }

      link = tmp + link;
      continue;
    }

    std::string::size_type pos = baseURL.rfind("/");
    if (pos != std::string::npos){
      tmp = baseURL.substr(0, pos+1);
    }
    link =  tmp + link;
  }
}

void RegularAlgo_LinksMaintenance::remove_Unbounded_links(const std::string& domainAddress)
{  
  auto result_renove_if = std::remove_if(m_links.begin(), m_links.end(), 
  [&](const std::string& link){return link.find(domainAddress) == std::string::npos;});

  m_links.erase(result_renove_if, m_links.end());
}

} // namespace se
