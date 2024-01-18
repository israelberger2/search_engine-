
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
    } catch(const se::MysqlLinksDataExeption& e){
        std::clog << "error from the MysqlWordLinks::insert: " << e.what() << "\n";
        return;
    }  

    for(auto& word : words){
        MysqlWordData wordData{};
        int wordID;
        try{
            // std::cout << "before get id from word" << '\n';
            
            wordID = wordData.insertAndGetID(word.first);
            // std::cout << "after get id from word" << '\n';
            
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
        // std::cout << "before insert to" << '\n';
        
        while(true){           
            try{    
                stmt->execute();
                break;
            } catch(const sql::SQLException& e){
                std::clog << "MysqlWordLinks::insert: " << e.what() << '\n';
                continue;      
            }
        }
        // std::cout << "after insert to" << '\n';
    }       
}

std::vector<std::string> db::MysqlWordLinks::getLinksForWord(const std::string& word)const
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

std::vector<int> db::MysqlWordLinks::getIDLinksForWord(const std::string& word)const
{
    std::string query = " SELECT Link.ID FROM Link \
        JOIN WordLink ON Link.ID = WordLink.LinkID \
        JOIN Word ON WordLink.WordID = Word.ID \
        WHERE Word.Token = ?";

    Connector connector{};

    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

    stmt->setString(1, word);

    std::vector<int> linksID;

    try{
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

        while(res->next()){
            linksID.push_back(res->getInt("id"));
        }
    } catch(const sql::SQLException& e){
        std::clog << "error from the MysqlWordLinks::getIDLinksForWord: " << e.what() << '\n';
    }

    return linksID;
}