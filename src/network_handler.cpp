#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
 
#include "network_handler.hpp"
#include "se_exceptions.hpp"
 

namespace se{

using json = nlohmann::json;

NetworkHandler::NetworkHandler()
: m_communicator(createSocketClient())
{}
 
std::vector<std::pair<std::string, int>> NetworkHandler::get_links(const std::vector<std::string>& query)const
{
    json j = query;
    std::string data = j.dump();
    const char* buffer = data.c_str();
     
    m_communicator.send_data(buffer, data.length());
     
    std::string result = m_communicator.receive_data();
     
    std::vector<std::pair<std::string, int>> links;

    try {
        json js = json::parse(result);
        links = js.get<std::vector<std::pair<std::string, int>>>();
    } catch (const json::parse_error& error) { 
        throw DataError("ERROR: json::runtime_error: " + std::string(error.what()));  
    }  

    return links;
}
 
int NetworkHandler::createSocketClient()const
{    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    std::string ip = "127.0.0.1";
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    int client_soket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_soket < 0){        
        throw SocketError("ERROR: unsuccessful to create socket and the socket failed");
    }
    
    int connect_sigen =  connect(client_soket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(connect_sigen < 0){
        throw(NetworkError("ERROR: DISCONNECTED the connect function failed"));
    }
    
    return client_soket;
}

} // namespace se
