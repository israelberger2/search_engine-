#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

#include "mysql_links.hpp"
#include "se_exceptions.hpp"


db::MysqlLinks::MysqlLinks()
{}

int db::MysqlLinks::insertAndGetLinkID(const std::string &link) const
{ 
  int idLink;

  try{ 
    std::string query = "INSERT INTO Link (Address) SELECT ? WHERE NOT EXISTS (SELECT * FROM Link WHERE Address = ?)";

    Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

    stmt->setString(1, link);
    stmt->setString(2, link);
    
    try{
      stmt->execute();
    } catch(const sql::SQLException& error){
      throw se::InValidLink("SQLerror::invalidLink");
    }

    std::string idQuery = "SELECT ID FROM Link WHERE Address = ? ";

    Connector resConnector{};
    std::unique_ptr<sql::PreparedStatement> resQuery = resConnector.get_conector(idQuery);
    resQuery->setString(1, link);
  
    std::unique_ptr<sql::ResultSet> linkResultes(resQuery->executeQuery());
    
    if(linkResultes->next()){
      idLink = linkResultes->getInt(1);
    }

  } catch(const sql::SQLException& e){
    throw(se::MysqlLinksExeption("error from the MysqlLinks::insertAndGetLinkID: " + std::string(e.what())));
  }
  return idLink;
}

std::string db::MysqlLinks::getLink(int id)const
{
  std::string link;

  try{
    std::string query = " SELECT Address FROM Link WHERE ID = ? ";

    Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
    
    stmt->setInt(1, id);

    std::unique_ptr<sql::ResultSet> resQuery(stmt->executeQuery());
    
    if(resQuery->next()){    
      link = resQuery->getString(1);
    }
  } catch(const sql::SQLException& e){
    throw(se::MysqlLinksExeption("error from the MysqlLinks::getLink: " + std::string(e.what())));
  }

  return link;
}

std::vector<std::string> db::MysqlLinks::getLinks(std::vector<int> linksID)const
{
  std::vector<std::string> links;

  try{
    std::string query = " SELECT Address FROM Link WHERE ID = ? ";

    size_t size = linksID.size() -1;
    for(size_t i = 0; i< size; ++i){
      query.append("OR ID = ? ");
    }

    Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
    
    for(size_t i = 0; i < linksID.size(); ++i){
      stmt->setInt(i+1, linksID[i]);
    }

    std::unique_ptr<sql::ResultSet> resQuery(stmt->executeQuery());
    
    while(resQuery->next()){ 
      links.push_back(resQuery->getString("Address"));
    }
  } catch(const sql::SQLException& e){
    throw(se::MysqlLinksExeption("error from the MysqlLinks::getLink: " + std::string(e.what())));
  }

  return links;
}
