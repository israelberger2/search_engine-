#include  "json.hpp" 
#include "net_client.hpp"
#include "se_exceptions.hpp"


namespace se{

using json = nlohmann::json;

NetClient::NetClient()
: m_socket()
, m_communicator(nullptr)
{}

std::vector<std::string> NetClient::load_query()
{           
    try{
        m_communicator =  m_socket.create_communicator();                
    } catch (const SocketError& error){        
        throw SocketError(error.what());
    }

    std::vector<std::string> res;
    
    try{
        std::string query = m_communicator->receive_data();
         
        json js = json::parse(query);
        res = js.get<std::vector<std::string>>();        
        return res;   
    } catch (const json::parse_error& error) {
        throw DataError(std::string("ERROR: json::runtime_error: " + std::string(error.what())));  
    }
}

void NetClient::send_data(const std::vector<std::pair<std::string, int>>& links)const
{    
    json j = links;
    std::string data = j.dump();
    const char* buffer = data.c_str();

    try{
        m_communicator->send_data(buffer, data.length());
    } catch (const NetworkError& error){
        throw NetworkError(error.what());
    }   
}

} // namespace se
