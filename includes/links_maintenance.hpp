#ifndef LINKS_MAINTENANCE_HPP
#define LINKS_MAINTENANCE_HPP

#include <vector>
#include <string>


namespace se{

class LinksMaintenance 
{
public:
    virtual ~LinksMaintenance() = default;

    virtual void setListLinks(std::vector<std::string>& links) = 0;
    virtual void fixLinks(const std::string& baseURL) = 0;
    virtual void remove_Unbounded_links(const std::string& domainAdrres) = 0;
};

} //namespace se
#endif
