#ifndef LINKS_MAINTENANCE_MANAGER_HPP
#define LINKS_MAINTENANCE_MANAGER_HPP

#include <vector>
#include <string>


namespace se{

class LinkMaintenanceManager
{
public:
    explicit LinkMaintenanceManager(std::vector<std::string>& links);
    ~LinkMaintenanceManager() = default;
    LinkMaintenanceManager(const LinkMaintenanceManager&) = default;
    LinkMaintenanceManager& operator= (const LinkMaintenanceManager&) = default;

    void handle(const std::string& url);

private:
    void fixLinks(const std::string& baseURL);
    void remove_external_links();
    void remove_invalid_links();

private:
    std::vector<std::string>& m_links;
};

} //namespace se
#endif
