#include <cppconn/prepared_statement.h>
#include  "json.hpp" 

#include "mysql_graph_data.hpp"
#include "mysql_links_data.hpp"
#include "connector.hpp"
#include "se_exceptions.hpp"


using json = nlohmann::json;

db::MysqlGraphData::MysqlGraphData()
{}

std::string db::MysqlGraphData::createJsonPages(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const
{
    std::vector<std::string> keys = buffer.getKeys();        
    json alllinksPages;

    for(auto key : keys){
        json links_array;
        for(auto& pair : buffer[key].first){
            json entry = {
                {"address", pair.first},
                {"count", pair.second}
            };
        
            links_array.push_back(entry);
        }

        json linksPage = {
            {"src", key},
            {"links", links_array}
        };
        alllinksPages.push_back(linksPage);
    }

    return alllinksPages.dump();
}

void db::MysqlGraphData::insert(se::SafeUnorderedMap<std::string, std::pair<Map, Map>>& buffer)const
{
    std::string json_pages = createJsonPages(buffer);
    std::string query = "CALL search_engine.inserLinksPages(?)";

    db::Connector connector{};
    auto stmt = connector.get_conector(query);

    stmt->setString(1, json_pages);

    try{
        stmt->execute();
    } catch(const sql::SQLException& error){
        std::cerr << "SQL Error Code: " << error.getErrorCode() <<  "SQL State: " << error.getSQLState() <<  "Error Message: " << error.what() << '\n';
    } 
}

void db::MysqlGraphData::insert(const Map& destinations, const std::string& src)const
{    
    MysqlLinksData sqlLinks{};
    int srcID;

    try{        
        srcID = sqlLinks.insertAndGetLinkID(src);            
    } catch(const se::MysqlLinksDataExeption& e){
        std::clog << "error from the MysqlGraphData::insert: " << e.what() << "/n";
        return;
    } 

    for(auto& des : destinations){
        int desID;
        try{
            desID = sqlLinks.insertAndGetLinkID(des.first);
        } catch(const se::MysqlLinksDataExeption& e){
            std::clog << "error from the MysqlGraphData::insert: " << e.what() << "/n";
            continue;
        }

        std::string query = "INSERT IGNORE INTO Graph (Src, Destination, Count) VALUES (?, ?, ?)";
        Connector connector{};
        std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
        stmt->setInt(1, srcID);
        stmt->setInt(2, desID);
        stmt->setInt(3, des.second);

        while (true ){
            try{ 
                stmt->execute();               
                break;
            } catch(const sql::SQLException& e){
                std::clog << "error from the MysqlGraphData::insert:  " << e.what() << '\n';   
                continue;
            }
        }
    }    
}
 
db::Graph db::MysqlGraphData::linkRelationships()const
{
    Graph graph{};

    std::string query = "SELECT DISTINCT Src FROM Graph ";

    Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

    std::vector<int> uniqueLinks;

    try{
        std::unique_ptr<sql::ResultSet> resultQuery(stmt->executeQuery());

        while(resultQuery->next()){
            uniqueLinks.push_back(resultQuery->getInt(1));
        }
    } catch(const sql::SQLException& e){
        throw se::NoGraph(e.what());
    }

    for(auto link : uniqueLinks){  
        try{  
            std::pair<std::string, std::vector<std::string>> resut = relatedLinksfromOneLink(link);
            graph.insert({resut.first,resut.second});
        }catch(const sql::SQLException& e){
            std::clog << "error from MysqlGraphData::linkRelationships/relatedLinksfromOneLink/linkRelated: " << e.what() << '\n';
            continue;
        }catch(const se::MysqlLinksDataExeption& e){
            std::clog << "error from MysqlGraphData::linkRelationships/relatedLinksfromOneLink/linksData: " << e.what() << '\n';
            continue;
        }
    }

    return graph;
}

std::vector<int> db::MysqlGraphData::linkRelated(int linkID)const
{
    std::string query = "SELECT Destination FROM Graph WHERE Src = ?";

    Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);
    stmt->setInt(1, linkID);

    std::unique_ptr<sql::ResultSet> resultQuery(stmt->executeQuery());

    std::vector<int> links;

    while(resultQuery->next()){
        int id = resultQuery->getInt(1);
        links.push_back(id);
    }
     
    return links;    
}

std::pair<std::string, std::vector<std::string>> db::MysqlGraphData::relatedLinksfromOneLink(int linkID)const
{
    std::vector<int> linksID = linkRelated(linkID); 

    MysqlLinksData linksData{};
    std::vector<std::string> linksAddresses =  linksData.getLink(linksID);
    std::string srcAddress = linksData.getLink(linkID);
     
    return std::pair<std::string, std::vector<std::string>>(srcAddress, linksAddresses);
}
    