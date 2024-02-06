#include <string>
#include <vector>
#include <sstream>
 
#include "string_split.hpp"


se::StringSplit::StringSplit(std::string& htmt_m_text)
: m_text(htmt_m_text)
{}

se::WordsMap se::StringSplit::parser()
{
    std::vector<std::string> words;
    std::istringstream iss(m_text);  
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
