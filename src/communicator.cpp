#include <arpa/inet.h>
#include <string>

#include "communicator.hpp"
#include "se_exceptions.hpp"


namespace se{

const int BUFFER_SIZE = 1024;

Communicator::Communicator(int fileDiscriptor)
: m_fileDiscriptor(fileDiscriptor)
{}

Communicator::~Communicator()
{
    close(m_fileDiscriptor);    
}

std::string Communicator::receive_data()const
{
    char buffer[BUFFER_SIZE];
    std::string data;
    int bytes_received = 0;

    do {
        bytes_received = recv(m_fileDiscriptor, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            throw NetworkError("ERROR: FAIL COMUNICATION the recv function failed");
        }
        data.append(buffer, bytes_received);
    } while (bytes_received == BUFFER_SIZE);

    return data;
}

void Communicator::send_data(const char* buffer,  size_t length)const
{
    int status = send(m_fileDiscriptor, buffer, length, 0);
    
    if(status < 0){
        throw NetworkError("ERROR: FAIL COMUNICATION the send function failed");
    }
}

} // namespace se
