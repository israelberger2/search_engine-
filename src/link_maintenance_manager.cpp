#include <algorithm>
 
#include "link_maintenance_manager.hpp"
#include "configuration.hpp"


namespace se{

LinkMaintenanceManager::LinkMaintenanceManager(std::vector<std::string>& links)
: m_links(links)
{}

void LinkMaintenanceManager::handle(const std::string& url)
{
  remove_invalid_links();
  fixLinks(url);
  remove_external_links();
}

void LinkMaintenanceManager::remove_invalid_links()
{
  auto result_remove_if =  std::remove_if(m_links.begin(), m_links.end(), 
  [&](const std::string& link){return (link  == "#" || link == "/f");});

  m_links.erase(result_remove_if, m_links.end()); 
}

void LinkMaintenanceManager::fixLinks(const std::string& baseURL)
{
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

void LinkMaintenanceManager::remove_external_links()
{  
  std::string StartOfLink = Config::getStartOfLink();

  auto result_renove_if = std::remove_if(m_links.begin(), m_links.end(), 
  [&](const std::string& link){return link.find(StartOfLink) == std::string::npos;});

  m_links.erase(result_renove_if, m_links.end());
}

} // namespace se
