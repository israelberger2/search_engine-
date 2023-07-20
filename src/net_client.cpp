#include <iostream>
#include  "json.hpp" 

#include "net_client.hpp"
#include "se_exceptions.hpp"
#include "acceptor.hpp"


namespace se{

using json = nlohmann::json;

NetClient::NetClient()
: m_communicator(nullptr)
{}

std::vector<std::string> NetClient::load_query()
{   
    if(m_communicator == nullptr){
        try{
            Acceptor acceptor;
            m_communicator =  acceptor.creat_communicator();
        } catch (const ServerSocketError& error){
            throw ServerSocketError(error.what());
        } catch (const SocketError& error){
            throw ServerSocketError(error.what());
        }
    }
    
    std::vector<std::string> res;
    
    try{
    std::string result = m_communicator->read();
        json js = json::parse(result);
        res = js.get<std::vector<std::string>>();
        return res;
    
    } catch (const json::parse_error& error) {
        throw DataError(std::string("ERROR: json::runtime_error: " + std::string(error.what())));  
    }
}

void NetClient::send_data(const std::vector<std::pair<std::string, size_t>>& links)const
{
    json j = links;
    std::string data = j.dump();
    const char* buffer = data.c_str();

    try{
        m_communicator->write(buffer, data.length());
    } catch (const NetworkError& error){
        throw NetworkError(error.what());
    }
}

} // namespace se
