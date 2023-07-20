#ifndef ACCEPTOR_HPP
#define ACCEPTOR_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>

#include "communicator.hpp"


namespace se{

class Acceptor
{
public:
    Acceptor();
    ~Acceptor();
    Acceptor(const Acceptor&) = delete;
    Acceptor& operator= (const Acceptor&) = delete;

    std::shared_ptr<Communicator> creat_communicator();

private:
    void init();
    void create_socket();

private:
    struct sockaddr_in m_server_addr;
    int m_fileDiscriptor;
};

} // namespace se
#endif