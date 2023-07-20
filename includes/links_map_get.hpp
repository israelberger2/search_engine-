#ifndef LINKSMAP_INSERT_HPP
#define LINKSMAP_INSERT_HPP

#include <unordered_map>
#include <vector>
#include <string>


namespace se{

using UrlMap = std::unordered_map<std::string,size_t>;

class LinksMapGet
{
public:
    virtual ~LinksMapGet() = default;

    virtual std::unordered_map<std::string, size_t> get_links(const std::string& key)const = 0;
    virtual bool is_here(const std::string& data)const = 0;
    virtual size_t size()const = 0;
    virtual std::unordered_map<std::string, UrlMap> get_map()const = 0;
};

} // namespace se
#endif
