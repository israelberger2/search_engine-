#include "links_map.hpp"
 
 
namespace se{

LinksMap::LinksMap()
: m_relatedLinks()
{}

void LinksMap::insert(const std::vector<std::string>& related_links,const std::string& link)
{    
    std::unordered_map<std::string, size_t> map_links;

    for (auto& link : related_links){
        map_links[link]++;
    }

    m_relatedLinks.insert(link,map_links);
}
 
std::unordered_map<std::string, size_t> LinksMap::get_links(const std::string& key)const
{  
    return m_relatedLinks.get_dada(key);
}

bool LinksMap::is_here(const std::string& data)const
{
    return m_relatedLinks.is_here(data);
}

size_t LinksMap::size()const
{
    return m_relatedLinks.size();
}

std::unordered_map<std::string, UrlMap> LinksMap::get_map()const
{
    return m_relatedLinks.getMap();
}

} // namespace se
