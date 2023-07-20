#include <iostream>

#include "acceptor.hpp"
#include "se_exceptions.hpp"


namespace se{

Acceptor::Acceptor()
{
    init();
    create_socket();
    listen(m_fileDiscriptor, 10);
    std::cout << "[+] Listening for connections on port 8080" << "\n";
}

Acceptor::~Acceptor()
{
    close(m_fileDiscriptor);
}

void Acceptor::init()
{
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(8080);
    m_server_addr.sin_addr.s_addr = INADDR_ANY;
}

void Acceptor::create_socket()
{
    m_fileDiscriptor = socket(AF_INET, SOCK_STREAM, 0);
    
    if(m_fileDiscriptor < 0){
        throw SocketError("unsuccessful to create socket");
    }
 
    int sigen = bind(m_fileDiscriptor, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr));
    if(sigen < 0){
        throw SocketError("unsuccessful to create socket");
    }
}

std::shared_ptr<Communicator> Acceptor::creat_communicator()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    int client_sock = accept(m_fileDiscriptor, (struct sockaddr*)&client_addr, &client_addr_size);
    if(client_sock <= 0){
        throw ServerSocketError("unsuccessful to create socket");
    }

    std::shared_ptr<Communicator> communicator = std::make_shared<Communicator>(client_sock);
    return communicator;
}

} // namespace se
