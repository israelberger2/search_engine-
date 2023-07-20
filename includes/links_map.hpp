#ifndef LINKS_MAP_HPP
#define LINKS_MAP_HPP

#include <vector>
#include <string>
#include <unordered_map>
 
#include "links_map_insertion.hpp"
#include "links_map_get.hpp"
#include "safe_unordered_map.hpp"


namespace se{

using UrlMap = std::unordered_map<std::string,size_t>;

class LinksMap : public LinksMamInsertion, public LinksMapGet
{
public:
  LinksMap();
  LinksMap(const LinksMap&) = default;
  ~LinksMap() = default;
  LinksMap& operator= (const LinksMap&) = default;

  std::unordered_map<std::string, size_t> get_links(const std::string& key)const override;
  void insert(const std::vector<std::string>& related_links,const std::string& link)override;
  bool is_here(const std::string& data)const override;
  size_t size()const override;
  std::unordered_map<std::string, UrlMap> get_map()const override;
   
private:
  SafeUnorderedMap<std::string, UrlMap> m_relatedLinks;
};

} // namespace se
#endif
