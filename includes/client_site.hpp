#ifndef CLIENT_SITE_HPP
#define CLIENT_SITE_HPP

#include "text_client.hpp"
#include "searcher.hpp"


namespace se{

class ClientSite
{
public:
    explicit ClientSite(Searcher& searcher, TextClient& tui);
    ~ClientSite() = default;
    ClientSite(const ClientSite&) = delete;
    ClientSite& operator= (const ClientSite&) = delete;

    void run()const;

private:
    Searcher& m_searcher;
    TextClient& m_tui;
};

} // namespace se

#endif
