#ifndef CLIENT_SITE_HPP
#define CLIENT_SITE_HPP

#include "text_client.hpp"


namespace se{

class ClientSite
{
public:
    ClientSite();
    ~ClientSite() = default;
    ClientSite(const ClientSite&) = delete;
    ClientSite& operator= (const ClientSite&) = delete;

    void run();

private:
    TextClient m_tui;
};

} // namespace se
#endif
