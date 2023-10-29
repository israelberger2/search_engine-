#include "client_site.hpp"
#include "text_client.hpp"
#include "proxy_searcher.hpp"
#include <memory>
#include <iostream>


using namespace se;
 
int main()
{
    // ProxySearcher proxy{};
    TextClient textClient{};

    ClientSite client(textClient);
    client.run();

    return 0;
}