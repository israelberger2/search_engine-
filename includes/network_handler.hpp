#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include <string>
#include <vector>
 
#include "communicator.hpp"


namespace se{

 
class NetworkHandler 
{
public:
    NetworkHandler();
    ~NetworkHandler() = default;
    NetworkHandler(const NetworkHandler&) = default;
    NetworkHandler& operator= (const NetworkHandler&) = default;

    std::vector<std::pair<std::string, int>> get_links(const std::vector<std::string>& querie)const;
    int createSocketClient()const;
    
private:
    Communicator m_communicator;
};

} // namespace se
#endif
