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

  Connector1 connector{};
  std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

  stmt->setString(1, link);
  stmt->setString(2, link);
  
  try{
    stmt->execute();
  } catch(const sql::SQLException& error){
    throw se::InValidLink("SQLerror::invalidLink");
  }

  std::string idQuery = "SELECT ID FROM Link WHERE Address = ? ";

  Connector1 resConnector{};
  std::unique_ptr<sql::PreparedStatement> resQuery = resConnector.get_conector(idQuery);
  resQuery->setString(1, link);
 
  std::unique_ptr<sql::ResultSet> linkResultes(resQuery->executeQuery());
  int idLink;
  
  if(linkResultes->next()){
    idLink = linkResultes->getInt(1);
  }

  return idLink;
}
