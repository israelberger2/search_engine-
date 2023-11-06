#include "client_site.hpp"
#include "text_client.hpp"
#include "network_handler.hpp"


using namespace se;

int main()
{
    TextClient textClient{};

    ClientSite client(textClient);
    client.run();

    return 0;
}