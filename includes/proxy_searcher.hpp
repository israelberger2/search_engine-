#ifndef PROXY_SEARCHER_HPP
#define PROXY_SEARCHER_HPP

#include "json.hpp" 
#include <string>
#include <vector>
#include  <utility>

#include "communicator.hpp"


namespace se{

 
class ProxySearcher 
{
public:
    ProxySearcher();
    ~ProxySearcher() = default;
    ProxySearcher(const ProxySearcher&) = default;
    ProxySearcher& operator= (const ProxySearcher&) = default;

    std::vector<std::pair<std::string, int>> get_links(const std::vector<std::string>& querie)const;
    int connect_to_server()const;
    
private:
    Communicator m_communicator;
};

} // namespace se
#endif
