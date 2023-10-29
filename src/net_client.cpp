// #include <iostream>
// #include  "json.hpp" 

// #include "net_client.hpp"
// #include "se_exceptions.hpp"
// #include "acceptor.hpp"


// namespace se{

// using json = nlohmann::json;

// NetClient::NetClient()
// : m_communicator(nullptr)
// {}

// std::vector<std::string> NetClient::load_query()
// {   
//     if(m_communicator == nullptr){
//         try{
//             Acceptor acceptor;
//             m_communicator =  acceptor.creat_communicator();
//         } catch (const ServerSocketError& error){
//             throw ServerSocketError(error.what());
//         } catch (const SocketError& error){
//             throw ServerSocketError(error.what());
//         }
//     }
    
//     std::vector<std::string> res;
    
//     try{
//         std::string result = m_communicator->receive_data();
//         json js = json::parse(result);
//         res = js.get<std::vector<std::string>>();
//         return res;
    
//     } catch (const json::parse_error& error) {
//         throw DataError(std::string("ERROR: json::runtime_error: " + std::string(error.what())));  
//     }
// }

// void NetClient::send_data(const std::vector<std::pair<std::string, int>>& links)const
// {
//     json j = links;
//     std::string data = j.dump();
//     const char* buffer = data.c_str();

//     try{
//         m_communicator->send_data(buffer, data.length());
//     } catch (const NetworkError& error){
//         throw NetworkError(error.what());
//     }
// }

// } // namespace se
#include <iostream>
#include  "json.hpp" 

#include "net_client.hpp"
#include "se_exceptions.hpp"


namespace se{

using json = nlohmann::json;

NetClient::NetClient()
: m_socket()
, m_communicator(nullptr)
{
    std::cout << "constractor of netclient" << '\n';
    
}

std::vector<std::string> NetClient::load_query()
{   
    // std::cout << "load wuery" << '\n';
    
    try{
        m_communicator =  m_socket.creat_communicator();
        std::cout << "find client" << '\n';
        
    } catch (const ServerSocketError& error){
        throw ServerSocketError(error.what());
    } catch (const SocketError& error){
        throw ServerSocketError(error.what());
    }

    std::vector<std::string> res;
    
    try{
        std::string result = m_communicator->receive_data();
        // std::cout << result << '\n';
        
        json js = json::parse(result);
        res = js.get<std::vector<std::string>>();
        std::cout << "end of load_query" << '\n';
        std::cout << "size_res: " << res.size() << '\n';
            
        return res;
    
    } catch (const json::parse_error& error) {
        throw DataError(std::string("ERROR: json::runtime_error: " + std::string(error.what())));  
    }
}

void NetClient::send_data(const std::vector<std::pair<std::string, int>>& links)const
{
    // std::cout << "send_data" << '\n';
    
    json j = links;
    std::string data = j.dump();
    const char* buffer = data.c_str();

    try{
        m_communicator->send_data(buffer, data.length());
        // m_communicator->closeConnection();
        // m_communicator.get();
    } catch (const NetworkError& error){
        // m_communicator->closeConnection();
        // m_communicator.get();
        throw NetworkError(error.what());
    }
    std::cout << "end of send data" << '\n';
    
}

} // namespace se
