#include "updater.hpp"
#include "configuration.hpp"
#include <iostream>
#include <thread>
#include "connector.hpp"
#include <chrono>
#include  "json.hpp" 

using json = nlohmann::json;
  

 

// void wordinsert(se::SafeUnorderedMap<std::string, std::pair<se::Map, se::Map>>& buffer)
// {
//     std::vector<std::string> keys = buffer.getKeys();        

//     for(auto key : keys){  
//         json words_array;
//         for(auto& pair : buffer[key].second){               
//                 json entry = {
//                 {"word", pair.first},
//                 {"count", pair.second}
//             };
//             words_array.push_back(entry);
//         }
        
//         std::string json_data = words_array.dump(); 
//         std::string query = "CALL search_engine.wordLinkInsert(?, ?)";
//         db::Connector connector{};
//         std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

//         stmt->setString(1, key);
//         stmt->setString(2, json_data);

//         try {
//             stmt->execute();
//         } catch (const sql::SQLException& error) {
//             std::cout << "error::" << error.what() << '\n';           
//         }
//     }                         
// }


void wordinsert(se::SafeUnorderedMap<std::string, std::pair<se::Map, se::Map>>& buffer)
{
    std::vector<std::string> keys = buffer.getKeys();        
    json all_pages;
    for(auto key : keys){  
        json words_array;
        for(auto& pair : buffer[key].second){               
                json entry = {
                {"word", pair.first},
                {"count", pair.second}
            };
            words_array.push_back(entry);
        }
        
        json page = {
            {"link", key},
            {"page", words_array}
        };
        all_pages.push_back(page);
    }
    
    std::string json_data = all_pages.dump(); 

    std::string query = "CALL search_engine.inserWordsPages(?)";
    db::Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

    stmt->setString(1, json_data);

    try {
        stmt->execute();
    } catch (const sql::SQLException& error) {
        std::cout << "error::" << error.what() << '\n';           
    }
                       
}
 

  
se::Updater::Updater(Publisher& publisher, db::GraphData& graph, db::WordLinks& words)
: m_buffer()
, m_mount(Config::getLinksMountForPagerank())
, m_publisher(publisher)    
, m_mtx()
, m_notMtx()
, m_graphData(graph)
, m_wordsData(words)
{}

void se::Updater::fill(std::pair<Map, Map>& resCrewl ,const std::string& url)
{  
    std::unique_lock<std::shared_mutex> locker(m_mtx);
     
    m_buffer.insert(url, resCrewl);
    if(m_buffer.size() >= m_mount){        
        SafeUnorderedMap<std::string, std::pair<Map, Map>> tempBuffer(std::move(m_buffer));
        locker.unlock();
        insert(tempBuffer);
        std::cout << "insert links" << '\n';     
        m_publisher.notify();
        wordinsert(tempBuffer);
    
        std::cout << "insert........................." << '\n';
    }    
}

void se::Updater::bufferFlush()
{    
    if(m_buffer.size() > 0){ 
        std::vector<std::string> keys = m_buffer.getKeys();
        
        for(auto key : keys){
            m_graphData.insert(m_buffer[key].first, key);
        }
         
        m_publisher.notify();
         
        for(auto key : keys){            
            m_wordsData.insert(m_buffer[key].second, key);
        }
    }  
}


void se::Updater::insert(SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)
{
    std::vector<std::string> keys = buffer.getKeys();        

    for(auto key : keys){
        json links_array;
        for(auto& pair : buffer[key].first){
            json entry = {
                {"address", pair.first},
                {"count", pair.second}
            };
            links_array.push_back(entry);
        }

        std::string json_links = links_array.dump();
    
        std::string query = "CALL search_engine.graphInsert(?, ?)";

        db::Connector connector{};
        auto stmt = connector.get_conector(query);

        stmt->setString(1, key);
        stmt->setString(2, json_links);
        try{
            stmt->execute();
        } catch(const sql::SQLException& error){
            std::cout << "SQL Error Code: " << error.getErrorCode() <<  "SQL State: " << error.getSQLState() <<  "Error Message: " << error.what() << std::endl;
        }
        
    } 
}
