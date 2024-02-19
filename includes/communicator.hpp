#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <string>


namespace se{

class Communicator
{
public:
    Communicator(int fileDiscriptor);
    ~Communicator();
    Communicator(const Communicator&) = delete;
    Communicator& operator= (const Communicator&) = delete;

    void send_data(const char* buffer, size_t length)const;
    std::string receive_data()const;

private:
    int m_fileDiscriptor;
};

} // namespace se
#endif