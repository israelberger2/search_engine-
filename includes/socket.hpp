#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>

#include "communicator.hpp"


namespace se{

class Socket
{
public:
    Socket();
    ~Socket() = default;
    Socket(const Socket&) = delete;
    Socket& operator= (const Socket&) = delete;

    std::shared_ptr<Communicator> creat_communicator()const;

private:
    void init();
    void create_socket();

private:
    struct sockaddr_in m_server_addr;
    int m_fileDiscriptor;
};

} // namespace se
#endif