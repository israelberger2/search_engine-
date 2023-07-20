#include <iostream> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "proxy_searcher.hpp"
#include "se_excaptions.hpp"
 

namespace se{

using json = nlohmann::json;

ProxySearcher::ProxySearcher()
: m_communicator(connect_to_server())
{}

std::vector<std::pair<std::string, size_t>> ProxySearcher::get_links(const std::vector<std::string>& query)const
{
    json j = query;
    std::string data = j.dump();
    const char* buffer = data.c_str();

    m_communicator.write(buffer, data.length());
    std::string result = m_communicator.read();

    std::vector<std::pair<std::string, size_t>> links;
    try {
        json js = json::parse(result);
        links = js.get<std::vector<std::pair<std::string, size_t>>>();
    } catch (const json::parse_error& error) { 
        throw DataError("ERROR: json::runtime_error: " + std::string(error.what()));  
    }  

    return links;
}
 
int ProxySearcher::connect_to_server()const
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int client_soket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_soket < 0){
        throw(NetworkError("ERROR: DISCONNECTED"));
    }
    
    int connect_sigen =  connect(client_soket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(connect_sigen < 0){
        throw(NetworkError("ERROR: DISCONNECTED"));
    }

    return client_soket;
}

} // namespace se
