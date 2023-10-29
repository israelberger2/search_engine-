#include <iostream> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "proxy_searcher.hpp"
#include "se_exceptions.hpp"
 

namespace se{

using json = nlohmann::json;

ProxySearcher::ProxySearcher()
: m_communicator(connect_to_server())
{
    std::cout << "proxy constructore" << '\n';
    
}

// ProxySearcher::~ProxySearcher()
// {
//     m_communicator.closeConnection();
// }

std::vector<std::pair<std::string, int>> ProxySearcher::get_links(const std::vector<std::string>& query)const
{
    json j = query;
    std::string data = j.dump();
    const char* buffer = data.c_str();
    std::cout << "befor send to server" << '\n';
    
    m_communicator.send_data(buffer, data.length());
    std::cout << "........................." << '\n';
    
    std::string result = m_communicator.receive_data();
    std::cout << "result: " << result << '\n';
    
    std::vector<std::pair<std::string, int>> links;
    try {
        json js = json::parse(result);
        links = js.get<std::vector<std::pair<std::string, int>>>();
    } catch (const json::parse_error& error) { 
        throw DataError("ERROR: json::runtime_error: " + std::string(error.what()));  
    }  

    return links;
}
 
int ProxySearcher::connect_to_server()const
{
    std::cout << "connect_to_server" << '\n';
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int client_soket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_soket < 0){
        std::cout << "client socket error" << '\n';
        
        throw(NetworkError("ERROR: DISCONNECTED"));
    }
    
    int connect_sigen =  connect(client_soket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(connect_sigen < 0){
        std::cout << "connect_sigen   error" << '\n';
        throw(NetworkError("ERROR: DISCONNECTED"));
    }
    
    std::cout << "end connect_to_server" << '\n';
    return client_soket;
}

} // namespace se
