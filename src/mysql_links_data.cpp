// #include <cppconn/prepared_statement.h>
// #include <cppconn/resultset.h>
// #include <memory>

// #include "mysql_links_data.hpp"
// #include "mysql_domain_data.hpp"


 

// int db::MysqlLinksData::insertAndGetLinkID(const se::Link& link)const
// {  
//   MysqlDomainData domainData;
//   int domainId  = domainData.getIDAndInsert(link.getDomain());
   
//   std::unique_ptr<sql::Connection> con = m_connector.get_conector();
//   con->setSchema("project");

//   std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
//     "INSERT INTO Link (Path, HostID)"
//     "SELECT ?, ? WHERE NOT EXISTS (SELECT * FROM Link WHERE HostID = ? AND Path = ?);")
//   );

//   stmt->setString(1, link.getPath());
//   stmt->setInt(2, domainId);
//   stmt->setInt(3, domainId);
//   stmt->setString(4, link.getPath());
//   stmt->execute();

//   std::unique_ptr<sql::PreparedStatement> resQuery(con->prepareStatement(
//   "SELECT ID FROM Link WHERE path = ? AND HostId = ?;")
//   );

//   resQuery->setString(1, link.getPath());
//   resQuery->setInt(2, domainId);

//   std::unique_ptr<sql::ResultSet> linkResultes(resQuery->executeQuery());

//   int idLink;
//   if(linkResultes->next()){
//     idLink = linkResultes->getInt("id");
//   }

//   return idLink;
// }

#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

#include "mysql_links_data.hpp"
#include "se_exceptions.hpp"


db::MysqlLinksData::MysqlLinksData()
: m_connector()
{}

int db::MysqlLinksData::insertAndGetLinkID(const std::string& link)const
{  
   
  std::unique_ptr<sql::Connection> con = m_connector.get_conector();
  con->setSchema("DBsearchEngine");

  std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
    "INSERT INTO Link (Address)"
    "SELECT ? WHERE NOT EXISTS (SELECT * FROM Link WHERE Address = ?);")
  );

  stmt->setString(1, link);
  stmt->setString(2, link);
  
  try{
    stmt->execute();
  } catch(const sql::SQLException& error){
    throw se::InValidLink("SQLerror::invalidLink");
  }

  std::unique_ptr<sql::PreparedStatement> resQuery(con->prepareStatement(
  "SELECT ID FROM Link WHERE Address = ? ;")
  );

  resQuery->setString(1, link);
 
  std::unique_ptr<sql::ResultSet> linkResultes(resQuery->executeQuery());

  int idLink;
  if(linkResultes->next()){
    idLink = linkResultes->getInt("id");
  }

  return idLink;
}
