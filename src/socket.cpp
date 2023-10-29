#include "socket.hpp"
#include "se_exceptions.hpp"


namespace se{

Socket::Socket()
{
    init();
    create_socket();
    int listenStatus = listen(m_fileDiscriptor, 10);
    if(listenStatus < 0){        
        throw SocketError("ERROR: listen function is fail");
    }
}

void Socket::init()
{
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(8080);
    m_server_addr.sin_addr.s_addr = INADDR_ANY;
}

void Socket::create_socket()
{
    m_fileDiscriptor = socket(AF_INET, SOCK_STREAM, 0);
    
    if(m_fileDiscriptor < 0){        
        throw SocketError("ERROR: unsuccessful to create socket and socket was fail");
    }
  
    int bindStatus = bind(m_fileDiscriptor, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr));
    if (bindStatus < 0){
        int yes = 1;
        if (setsockopt(m_fileDiscriptor, SOL_SOCKET, SO_REUSEADDR, (void*)&yes, sizeof(yes)) < 0){
            throw SocketError("unsuccessful to create socket and setsockopt function was fail");
        }
    }
}

std::shared_ptr<Communicator> Socket::creat_communicator()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    int client_socket = accept(m_fileDiscriptor, (struct sockaddr*)&client_addr, &client_addr_size);
    if(client_socket < 0){
        throw SocketError("ERROR: accept function is fail");
    }

    std::shared_ptr<Communicator> communicator = std::make_shared<Communicator>(client_socket);
    return communicator;
}

} // namespace se
