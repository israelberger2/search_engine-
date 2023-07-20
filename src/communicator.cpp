#include <iostream>

#include <arpa/inet.h>
 
#include "communicator.hpp"
#include "se_exceptions.hpp"


namespace se{

Communicator::Communicator(int fileDiscriptoronst)
: m_fileDiscriptoronst(fileDiscriptoronst)
{}

Communicator::~Communicator()
{
    close(m_fileDiscriptoronst);
}

std::string Communicator::read()const
{
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    std::string data;
    int bytes_received = 0;

    do {
        bytes_received = recv(m_fileDiscriptoronst, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            throw NetworkError("FAIL COMUNICATION");
        }
        data.append(buffer, bytes_received);
    } while (bytes_received == BUFFER_SIZE);

    return data;
}

void Communicator::write(const char* buffer,  size_t length)const
{
    int status = send(m_fileDiscriptoronst, buffer, length, 0);
    if(status <= 0){
        throw NetworkError("FAIL COMUNICATION");
    }
}

} // namespace se
