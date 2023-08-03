#include <cppconn/prepared_statement.h>
#include <memory>

#include "mysql_word_links.hpp"
#include "mysql_links_data.hpp"
#include "mysql_word_data.hpp"
#include "se_exceptions.hpp"


db::MysqlWordLinks::MysqlWordLinks()
: m_connector()
{}
 
void db::MysqlWordLinks::insert(const WordsMap& words, const std::string& link)
{   
    MysqlLinksData linksData{};
    int linkID;

    try{
        linkID = linksData.insertAndGetLinkID(link);
    } catch(const se::InValidLink& error){
        return;
    }

    for(auto& word : words){
        MysqlWordData wordData{};
        int wordID;
        try{
            wordID = wordData.insertAndGetID(word.first);
        } catch(const se::InValidWord& error){
            continue;
        }
        
        std::unique_ptr<sql::Connection> con = m_connector.get_conector();
        con->setSchema("DBsearchEngine");
    
        std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
        "INSERT INTO WordLink (WordID, LinkID, Count) "
        "SELECT ?, ?, ? "
        "WHERE NOT EXISTS (SELECT * FROM WordLink WHERE WordID = ? AND LinkID = ?)")
        );

        stmt->setInt(1, wordID);
        stmt->setInt(2, linkID);
        stmt->setInt(3, word.second);
        stmt->setInt(4, wordID);
        stmt->setInt(5, linkID);
        stmt->execute();
    }
}

std::vector<std::string> db::MysqlWordLinks::getLinksForWord(const std::string& word)
{
    std::unique_ptr<sql::Connection> con = m_connector.get_conector();
    con->setSchema("DBsearchEngine");

    std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
    " SELECT Link.Address FROM Link"
    " JOIN WordLink ON Link.ID = WordLink.LinkID"
    " JOIN Word ON WordLink.WordID = Word.ID"
    " WHERE Word.Token = ?")
    );

    stmt->setString(1, word);
    
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    std::vector<std::string> links;

    while(res->next()){
        links.push_back(res->getString(1));
    }

    return links;
}

std::vector<int> db::MysqlWordLinks::getIDLinksForWord(const std::string& word)
{
    std::unique_ptr<sql::Connection> con = m_connector.get_conector();
    con->setSchema("DBsearchEngine");

    std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
    " SELECT Link.ID FROM Link"
    " JOIN WordLink ON Link.ID = WordLink.LinkID"
    " JOIN Word ON WordLink.WordID = Word.ID"
    " WHERE Word.Token = ?")
    );

    stmt->setString(1, word);
    
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    std::vector<int> linksID;

    while(res->next()){
        linksID.push_back(res->getInt("id"));
    }

    return linksID;
}