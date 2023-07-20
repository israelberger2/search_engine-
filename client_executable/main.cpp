#include "client_site.hpp"
#include "text_client.hpp"
#include "proxy_searcher.hpp"


using namespace se;

int main()
{
    ProxySearcher proxy{};
    TextClient textClient{};
    
    ClientSite client(proxy, textClient);
    client.run();

    return 0;
}