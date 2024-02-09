#include <vector>
#include <sstream>
 
#include "string_split.hpp"


se::WordsMap se::split(std::string& htmt_text)
{
    std::vector<std::string> words;
    std::istringstream iss(htmt_text);  
    WordsMap allWords;
    std::string word;
    while (iss >> word) {
        bool isValidWord = true;

        for (char c : word) {
            if (!std::isalpha(c)) {
                isValidWord = false;
                break;
            }
        }

        if (isValidWord && word.length() >= 3){
            allWords[word]++;        
        }
    }

    return allWords;
}
