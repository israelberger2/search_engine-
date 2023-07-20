#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

#include "mysql_domain_data.hpp"


int db::MysqlDomainData::getIDAndInsert(const std::string& domain)
{    
    std::unique_ptr<sql::Connection> con = m_connector.get_conector();
    con->setSchema("project");
     
    std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
        "INSERT INTO Domain (Host) SELECT ? WHERE NOT EXISTS (SELECT * FROM Domain WHERE Host = ?);")
    );
    
    stmt->setString(1, domain);
    stmt->setString(2, domain);
    stmt->execute();
     
    std::unique_ptr<sql::PreparedStatement> IDstmt(con->prepareStatement(
        "SELECT ID FROM Domain WHERE Host = ?;")
    );

    IDstmt->setString(1, domain);

    std::unique_ptr<sql::ResultSet> res(IDstmt->executeQuery());
    int domainId;
    
    if (res->next()){
        domainId = res->getInt("id");
    }

    return domainId;
}