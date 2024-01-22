#include <map>
#include <iostream>
 
#include "connector.hpp"
#include  "json.hpp" 
  
using json = nlohmann::json;

 void tes()
{
    json j = {
        {'p' , "okoko"},
        {2 , 3}
    };

    std::cout << "1:" << j[2] << "2:" << j[1] << '\n';
    
}

int main() {
    tes();
     std::map<std::string, int> myMap = {
        {"dddpo11111111111111111111", 10},
        {"rrrrrr", 48}
        // Add more entries as needed
    };

    json j_array;

    for (const auto& pair : myMap) {
        json entry = {
            {"word", pair.first},
            {"count", pair.second}
        };
        j_array.push_back(entry);
    }
 
    std::string json_data = "....j_array.dump()";
    // std::cout << json_data << '\n';
    // std::string source_link = "sourse_linksssssss";
 
    std::string query = "CALL search_engine.prc(?)";

    db::Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

    stmt->setString(1, json_data);

    try {
        stmt->execute();
        std::cout << "Procedure executed successfully." << std::endl;
    } catch (const sql::SQLException& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }
    // The rest of your code remains the same...

    return 0;
}





 