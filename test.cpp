#include <map>
#include <iostream>
 
#include "connector.hpp"
#include  "json.hpp" 
  
using json = nlohmann::json;

 
int main() {
     std::map<std::string, int> myMap = {
        {"dddpo", 10},
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
 
    std::string json_data = j_array.dump();
    std::cout << json_data << '\n';
    std::string source_link = "sourse_linksssssss";
 
    std::string query = "CALL search_engine.wordLinkInsert(?, ?)";

    db::Connector connector{};
    std::unique_ptr<sql::PreparedStatement> stmt = connector.get_conector(query);

    stmt->setString(1, source_link);
    stmt->setString(2, json_data);

    try {
        stmt->execute();
        std::cout << "Procedure executed successfully." << std::endl;
    } catch (const sql::SQLException& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }
    // The rest of your code remains the same...

    return 0;
}





 