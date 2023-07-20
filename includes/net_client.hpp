#ifndef NET_CLIENT_HPP
#define NET_CLIENT_HPP

#include <vector>
#include <string>
#include <memory>

#include "client.hpp"
#include "communicator.hpp"


namespace se{

class NetClient : public Client
{
public:
    NetClient();
    ~NetClient() = default;
    NetClient(const NetClient&) = delete;
    NetClient& operator= (const NetClient&) = delete;

    std::vector<std::string> load_query() override;
    void send_data(const std::vector<std::pair<std::string, size_t>>& links)const override;

private:
    std::shared_ptr<Communicator> m_communicator;
};

} // namespace se
#endif