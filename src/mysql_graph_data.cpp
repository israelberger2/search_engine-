// #include <cppconn/prepared_statement.h>

// #include "mysql_graph_data.hpp"
// #include "mysql_links_data.hpp"
// #include "se_exceptions.hpp"


// db::MysqlGraphData::MysqlGraphData()
// : m_connector()
// {}

// void db::MysqlGraphData::insert(const Map& destinations, const std::string& src)
// {    
//     MysqlLinksData sqlLinks{};
//     int srcID;

//     try{        
//         srcID = sqlLinks.insertAndGetLinkID(src);
//     } catch(const se::InValidLink& error){         
//         return;
//     }

//     for(auto& des : destinations){
//         int desID;
//         try{
//             desID = sqlLinks.insertAndGetLinkID(des.first);
//         }catch(const se::InValidLink& error){
//             continue;
//         }
//         std::unique_ptr<sql::Connection> con = m_connector.get_conector();
//         con->setSchema("DBsearchEngine");
 
//         std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
//         "INSERT INTO Graph (Src, Destination, Count) "
//         "SELECT ?, ?, ? "
//         "WHERE NOT EXISTS (SELECT * FROM Graph WHERE Src = ? AND Destination = ?)")
//         );

//         stmt->setInt(1, srcID);
//         stmt->setInt(2, desID);
//         stmt->setInt(3, des.second);
//         stmt->setInt(4, srcID);
//         stmt->setInt(5, desID);
//         stmt->execute();
//     }
// }

#include <cppconn/prepared_statement.h>

#include "mysql_graph_data.hpp"
#include "mysql_links_data.hpp"
#include "se_exceptions.hpp"


db::MysqlGraphData::MysqlGraphData()
: m_connector()
{}

void db::MysqlGraphData::insert(const Map& destinations, const std::string& src)
{    
    MysqlLinksData sqlLinks{};
    int srcID;

    try{        
        srcID = sqlLinks.insertAndGetLinkID(src);
    } catch(const se::InValidLink& error){         
        return;
    }

    for(auto& des : destinations){
        int desID;
        try{
            desID = sqlLinks.insertAndGetLinkID(des.first);
        }catch(const se::InValidLink& error){
            continue;
        }

        std::string query = "INSERT INTO Graph (Src, Destination, Count) \
        SELECT ?, ?, ? WHERE NOT EXISTS (SELECT * FROM Graph WHERE Src = ? AND Destination = ?)";
        
        Connector1 connector{};
        std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
      
        stmt->setInt(1, srcID);
        stmt->setInt(2, desID);
        stmt->setInt(3, des.second);
        stmt->setInt(4, srcID);
        stmt->setInt(5, desID);
        stmt->execute();
    }
}

 