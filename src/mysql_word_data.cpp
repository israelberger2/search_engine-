#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

#include "mysql_word_data.hpp"
#include "connector.hpp"
#include "se_exceptions.hpp"


db::MysqlWordData::MysqlWordData()
{}

int db::MysqlWordData::insertAndGetID(const std::string &word)const
{
  std::string query = "INSERT INTO Word (Token) SELECT ? WHERE NOT EXISTS (SELECT * FROM Word WHERE Token = ?);";

  Connector1 connector{};
  std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

  stmt->setString(1, word);
  stmt->setString(2, word);

  try{
    stmt->execute();
  }catch(const sql::SQLException& error){    
    throw se::InValidWord("SQLerror::invalidWord");
  }

  std::string resQuery = "SELECT ID FROM Word WHERE Token = ?;";
  
  Connector1 resConnector{};
  std::unique_ptr<sql::PreparedStatement> IDresult = resConnector.get_conector(resQuery);
  IDresult->setString(1, word);

  std::unique_ptr<sql::ResultSet> res(IDresult->executeQuery());
  int wordId = 0;
  
  if(res->next()){
    wordId = res->getInt(1);
  }

  return wordId;
}

std::vector<int> db::MysqlWordData::getWordsID(const std::vector<std::string>& queries)const
{
  if(queries.empty()){    
    return std::vector<int>{};
  }
   
  std::string query = "SELECT ID FROM Word WHERE TOKEN = ?";
  size_t size = 0;
  
  while(size++ < queries.size()-1){
    std::string supplementary = " OR Token = ?";
    query += supplementary;
  }
   
  Connector1 connector{};
  std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
  
  for(size_t i  = 0; i < queries.size(); ++i){
    stmt->setString(i+1, queries[i]);
  }
  
  std::unique_ptr<sql::ResultSet> linkResultes(stmt->executeQuery());

  std::vector<int> result;

  while(linkResultes->next()){
    result.push_back(linkResultes->getInt("id"));
  }

  return result;
}
