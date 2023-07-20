#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 

namespace se{

class Communicator
{
public:
    explicit Communicator(int fileDiscriptoronst);
    ~Communicator();
    Communicator(const Communicator&) = delete;
    Communicator& operator= (const Communicator&) = delete;

    void write(const char* buffer, size_t length)const;
    std::string read()const;

private:
    int m_fileDiscriptoronst;
};

} // namespace se
#endif