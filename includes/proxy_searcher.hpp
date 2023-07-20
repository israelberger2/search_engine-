#ifndef PROXY_SEARCHER_HPP
#define PROXY_SEARCHER_HPP

#include "json.hpp" 
#include <string>
#include <vector>
#include  <utility>

#include "searcher.hpp"
#include "communicator.hpp"


namespace se{

 
class ProxySearcher : public Searcher
{
public:
    ProxySearcher();
    ~ProxySearcher() = default;
    ProxySearcher(const ProxySearcher&) = default;
    ProxySearcher& operator= (const ProxySearcher&) = default;

    std::vector<std::pair<std::string, size_t>> get_links(const std::vector<std::string>& querie)const override;
    int connect_to_server()const;
    
private:
    Communicator m_communicator;
};

} // namespace se
#endif
