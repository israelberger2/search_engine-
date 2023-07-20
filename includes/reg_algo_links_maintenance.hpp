#ifndef REG_ALGO_LINKS_MAINTENANCE_HPP
#define REG_ALGO_LINKS_MAINTENANCE_HPP

#include <vector>
#include <string>

#include "links_maintenance.hpp"


namespace se{

class RegularAlgo_LinksMaintenance : public LinksMaintenance
{
public:
    RegularAlgo_LinksMaintenance();
    ~RegularAlgo_LinksMaintenance() = default;
    RegularAlgo_LinksMaintenance(const RegularAlgo_LinksMaintenance&) = default;
    RegularAlgo_LinksMaintenance& operator= (const RegularAlgo_LinksMaintenance&) = default;

    void setListLinks(std::vector<std::string>& links)override;
    void fixLinks(const std::string& baseURL)override;
    void remove_Unbounded_links(const std::string& domainAdrres)override;

private:
    void remove_invalid_links();

private:
    std::vector<std::string> m_links;
};

} //namespace se
#endif
