
#include <cppconn/prepared_statement.h>
#include <memory>
#include <iostream>
#include  "json.hpp" 

#include "mysql_word_links.hpp"
#include "mysql_links_data.hpp"
#include "mysql_word_data.hpp"
#include "se_exceptions.hpp"

using json = nlohmann::json;
  

db::MysqlWordLinks::MysqlWordLinks()
{}

std::string db::MysqlWordLinks::createJsonPages(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const
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
    
    return all_pages.dump();
}

void db::MysqlWordLinks::insert(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const
{
    std::string json_data = createJsonPages(buffer);
    std::string query = "CALL search_engine.inserWordsPages(?)";

    db::Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

    stmt->setString(1, json_data);

    try {
        stmt->execute();
    } catch (const sql::SQLException& error) {
        std::cerr << "error::" << error.what() << '\n';           
    }                      
}

void db::MysqlWordLinks::insert(const Map& words, const std::string& link)const
{   
    MysqlLinksData linksData{};
    int linkID;

    try{
        linkID = linksData.insertAndGetLinkID(link);
    } catch(const se::MysqlLinksDataExeption& e){
        std::clog << "error from the MysqlWordLinks::insert: " << e.what() << "\n";
        return;
    }  

    for(auto& word : words){
        MysqlWordData wordData{};
        int wordID;
        try{            
            wordID = wordData.insertAndGetID(word.first);            
        } catch(const se::MysqlWordDataException& e){
            std::clog << "error from the MysqlWordLinks::insert: " << e.what() << '\n';
            continue;
        }  

        std::string query = "INSERT IGNORE INTO WordLink (WordID, LinkID, Count) VALUES (?, ?, ?)";

        Connector connector{};
        std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

        stmt->setInt(1, wordID);
        stmt->setInt(2, linkID);
        stmt->setInt(3, word.second);
         
        while(true){           
            try{    
                stmt->execute();
                break;
            } catch(const sql::SQLException& e){
                std::clog << "MysqlWordLinks::insert: " << e.what() << '\n';
                continue;      
            }
        }
    }       
}

std::vector<std::string> db::MysqlWordLinks::getLinksContainingWord(const std::string& word)const
{
    std::string query = "SELECT Link.Address FROM Link \
        JOIN WordLink ON Link.ID = WordLink.LinkID \
        JOIN Word ON WordLink.WordID = Word.ID \
        WHERE Word.Token = ?";

    Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query); 

    stmt->setString(1, word);
        
    std::vector<std::string> links;

    try{
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        while(res->next()){         
            links.push_back(res->getString(1));
        }
    } catch(const sql::SQLException& e){
        std::clog << "error from the MysqlWordLinks::getLinksForWord: " << e.what() << '\n';
    }

    return links;
}
