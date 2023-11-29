// #include <cppconn/prepared_statement.h>
// #include <memory>
// #include <iostream>

// #include "mysql_word_links.hpp"
// #include "mysql_links_data.hpp"
// #include "mysql_word_data.hpp"
// #include "se_exceptions.hpp"


// db::MysqlWordLinks::MysqlWordLinks()
// {}
 
// void db::MysqlWordLinks::insert(const WordsMap& words, const std::string& link)const
// {   try{
//         MysqlLinksData linksData{};
//         int linkID;

//         try{
//             linkID = linksData.insertAndGetLinkID(link);
//         } catch(const se::InValidLink& error){
//             return;
//         }

//         for(auto& word : words){
//             MysqlWordData wordData{};
//             int wordID;
//             try{
//                 wordID = wordData.insertAndGetID(word.first);
//             } catch(const se::InValidWord& error){
//                 continue;
//             }
            
// /             std::string query = "INSERT INTO WordLink (WordID, LinkID, Count) SELECT ?, ?, ? \
                 WHERE NOT EXISTS (SELECT * FROM WordLink WHERE WordID = ? AND LinkID = ?)";

//             Connector connector{};
//             std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
    
//             stmt->setInt(1, wordID);
//             stmt->setInt(2, linkID);
//             stmt->setInt(3, word.second);
//             stmt->setInt(4, wordID);
//             stmt->setInt(5, linkID);
//             stmt->execute();
//         }
//     } catch(const sql::SQLException& e){
//         std::cout << "MysqlWordLinks::insert" << e.what() << '\n';      
//     }
// }

// std::vector<std::string> db::MysqlWordLinks::getLinksForWord(const std::string& word)const
// {
//     std::vector<std::string> links;

//     try{
//         std::string query = "SELECT Link.Address FROM Link \
             JOIN WordLink ON Link.ID = WordLink.LinkID \
             JOIN Word ON WordLink.WordID = Word.ID \
             WHERE Word.Token = ?";

//         Connector connector{};
//         std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query); 
    
//         stmt->setString(1, word);
        
//         std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

//         while(res->next()){
//             links.push_back(res->getString(1));
//         }
//     } catch(const sql::SQLException& e){
//         std::cout << "MysqlWordLinks::getLinksForWord" << e.what() << '\n';      
//     }

//     return links;
// }

// std::vector<int> db::MysqlWordLinks::getIDLinksForWord(const std::string& word)const
// {
//     std::vector<int> linksID;

//     try{
//         std::string query = " SELECT Link.ID FROM Link \
//             JOIN WordLink ON Link.ID = WordLink.LinkID \
//             JOIN Word ON WordLink.WordID = Word.ID \
//             WHERE Word.Token = ?";

//         Connector connector{};

//         std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

//         stmt->setString(1, word);
        
//         std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

//         while(res->next()){
//             linksID.push_back(res->getInt("id"));
//         }
//     } catch(const sql::SQLException& e){
//         std::cout << "getIDLinksForWord" << e.what() << '\n';
        
//     }

//     return linksID;
// }

#include <cppconn/prepared_statement.h>
#include <memory>
#include <iostream>

#include "mysql_word_links.hpp"
#include "mysql_links_data.hpp"
#include "mysql_word_data.hpp"
#include "se_exceptions.hpp"


db::MysqlWordLinks::MysqlWordLinks()
{}
 
void db::MysqlWordLinks::insert(const WordsMap& words, const std::string& link)const
{   
    MysqlLinksData linksData{};
    int linkID;

    try{
        linkID = linksData.insertAndGetLinkID(link);
    } catch(const se::InValidLink& error){
        return;
    } catch(const sql::SQLException& e){
        std::cout << "MysqlWordLinks::insert, after function: linksData.insertAndGetLinkID:  " << e.what() << '\n';      
    }

    for(auto& word : words){
        MysqlWordData wordData{};
        int wordID;
        try{
            wordID = wordData.insertAndGetID(word.first);
        } catch(const se::InValidWord& error){
            std::cout << "MysqlWordLinks/insert/wordData.insertAndGetID: " << error.what() << '\n';
            
            continue;
        } catch(const sql::SQLException& e){
            std::cout << "MysqlWordLinks::insert, after function: linksData.insertAndGetLinkID: inside forloop  " << e.what() << '\n';      
        }

        
        // std::string query = "INSERT INTO WordLink (WordID, LinkID, Count) SELECT ?, ?, ? \
        //     WHERE NOT EXISTS (SELECT * FROM WordLink WHERE WordID = ? AND LinkID = ?)";
        while(true){
            try{
                std::string query = "INSERT IGNORE INTO WordLink (WordID, LinkID, Count) VALUES (?, ?, ?)";

                Connector connector{};
                std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
        
                stmt->setInt(1, wordID);
                stmt->setInt(2, linkID);
                stmt->setInt(3, word.second);
                
                stmt->execute();
                break;
            } catch(const sql::SQLException& e){
                std::cout << "MysqlWordLinks::insert....  " << e.what() << '\n';
                continue;      
            }
        }
    }       
   
}

std::vector<std::string> db::MysqlWordLinks::getLinksForWord(const std::string& word)const
{
    std::vector<std::string> links;

    try{
        std::string query = "SELECT Link.Address FROM Link \
            JOIN WordLink ON Link.ID = WordLink.LinkID \
            JOIN Word ON WordLink.WordID = Word.ID \
            WHERE Word.Token = ?";

        Connector connector{};
        std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query); 
    
        stmt->setString(1, word);
        
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

        while(res->next()){
            links.push_back(res->getString(1));
        }
    } catch(const sql::SQLException& e){
        std::cout << "MysqlWordLinks::getLinksForWord" << e.what() << '\n';      
    }

    return links;
}

std::vector<int> db::MysqlWordLinks::getIDLinksForWord(const std::string& word)const
{
    std::vector<int> linksID;

    try{
        std::string query = " SELECT Link.ID FROM Link \
            JOIN WordLink ON Link.ID = WordLink.LinkID \
            JOIN Word ON WordLink.WordID = Word.ID \
            WHERE Word.Token = ?";

        Connector connector{};

        std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

        stmt->setString(1, word);
        
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

        while(res->next()){
            linksID.push_back(res->getInt("id"));
        }
    } catch(const sql::SQLException& e){
        std::cout << "getIDLinksForWord" << e.what() << '\n';
        
    }

    return linksID;
}