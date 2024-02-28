#include <iostream>
#include <sstream>

#include "text_client.hpp"
#include "se_exceptions.hpp"


namespace se{

std::vector<std::string> TextClient::load_query() 
{
    std::cout << "enter a keyword. to exit the program write exit\n";

    std::string input;
    std::vector<std::string> keywords;
    while (std::getline(std::cin, input)){
        std::istringstream iss(input);
        std::string query;
        iss >> query;
 
       if(query == "exit"){
            throw Exit("");
        }

        if(is_valid_input(input)){
            keywords = get_substrings(input);
            break;
        }     
    }  
    
    return keywords; 
} 


bool TextClient::is_valid_input(const std::string& input)const
{
    if (input.length() >= 3){
        for (size_t i = 0; i < input.length() - 1; i++){
            if(input[i] != ' ' && input[i+1] != ' ') {
                return true;  
            }
        }
    }

    std::cout << "Please enter a keyword with at least three letters" << "/n";
    
    return false; 
}

std::vector<std::string> TextClient::get_substrings(const std::string& input)const
{
    std::istringstream iss(input);
    std::string word;

    std::vector<std::string> substrings;

    while (iss >> word){
        if(word.size() >= 2){
            substrings.push_back(word);
        }
    }

    return substrings;
}

void TextClient::send_data(const std::vector<std::pair<std::string, int>>& links)const
{    
    if(links.size() == 0){
        std::cout << "The keyword wes not found" << "\n";
    } else {        
        for(auto& link : links){
            std::cout << link.first << "\n";
        }
    }
}

} // namespace se
