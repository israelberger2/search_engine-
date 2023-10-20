#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

#include "mysql_links_data.hpp"
#include "se_exceptions.hpp"


db::MysqlLinksData::MysqlLinksData()
{}

int db::MysqlLinksData::insertAndGetLinkID(const std::string &link) const
{  
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
  int idLink;
  
  if(linkResultes->next()){
    idLink = linkResultes->getInt(1);
  }

  return idLink;
}

std::string db::MysqlLinksData::getLink(int id)const
{
  std::string query = " SELECT Address FROM Link WHERE ID = ? ";

  Connector connector{};
  std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
  
  stmt->setInt(1, id);

  std::string link;

  std::unique_ptr<sql::ResultSet> resQuery(stmt->executeQuery());
  
  if(resQuery->next()){    
    link = resQuery->getString(1);
  }

  return link;
}

std::vector<std::string> db::MysqlLinksData::getLink(std::vector<int> linksID)const
{
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

  std::vector<std::string> links;

  std::unique_ptr<sql::ResultSet> resQuery(stmt->executeQuery());
  
  while(resQuery->next()){ 
    links.push_back(resQuery->getString("Address"));
  }
     
  return links;
}
