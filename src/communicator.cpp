// #include <iostream>
// #include <arpa/inet.h>
 
// #include <sys/socket.h>
// #include <arpa/inet.h>

// #include "communicator.hpp"
// #include "se_exceptions.hpp"


// namespace se{

// Communicator::Communicator(int fileDiscriptor)
// : m_fileDiscriptor(fileDiscriptor)
// {}

// void Communicator::closeConnection()
// {
//     close(m_fileDiscriptor);
// }

// std::string Communicator::receive_data()const
// {
//     const int BUFFER_SIZE = 1024;
//     char buffer[BUFFER_SIZE];
//     std::string data;
//     int bytes_received = 0;

//     do {
//         bytes_received = recv(m_fileDiscriptor, buffer, BUFFER_SIZE, 0);
//         if (bytes_received <= 0) {
//             throw NetworkError("FAIL COMUNICATION");
//         }
//         data.append(buffer, bytes_received);
//     } while (bytes_received == BUFFER_SIZE);

//     return data;
// }

// void Communicator::send_data(const char* buffer,  size_t length)const
// {
//     int status = send(m_fileDiscriptor, buffer, length, 0);
//     if(status <= 0){
//         throw NetworkError("FAIL COMUNICATION");
//     }
// }

// } // namespace se

#include <iostream>
#include <arpa/inet.h>
 
#include <sys/socket.h>
#include <arpa/inet.h>

#include "communicator.hpp"
#include "se_exceptions.hpp"


namespace se{

Communicator::Communicator(int fileDiscriptor)
: m_fileDiscriptor(fileDiscriptor)
{}

Communicator::~Communicator()
{
    close(m_fileDiscriptor);
    std::cout << "distructore communicator" << '\n';
    
}

void Communicator::closeConnection()
{
    std::cout << "close" << '\n';
    
    close(m_fileDiscriptor);
}

std::string Communicator::receive_data()const
{
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    std::string data;
    int bytes_received = 0;

    do {
        bytes_received = recv(m_fileDiscriptor, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            perror("Failed to receive data");
            throw NetworkError("FAIL COMUNICATION");
        }
        data.append(buffer, bytes_received);
    } while (bytes_received == BUFFER_SIZE);

    return data;
}

void Communicator::send_data(const char* buffer,  size_t length)const
{
    int status = send(m_fileDiscriptor, buffer, length, 0);
    
    if(status <= 0){
        std::cout << ".....FAIL COMUNICATION" << '\n';
        
        throw NetworkError("FAIL COMUNICATION");
    }
    std::cout << "end of send data" << '\n';
    
}

} // namespace se
