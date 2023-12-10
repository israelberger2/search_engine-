#include <string>
#include <vector>
#include <sstream>
#include <cctype>

#include "string_split.hpp"


se::StringSplit::StringSplit(std::string& htmt_m_text)
: m_text(htmt_m_text)
{}

// std::unordered_map<std::string, size_t> se::StringSplit::parser()
// {
//     std::string::iterator first_word = m_text.begin();
//     std::string::iterator end_word;
//     std::string::iterator end_text = m_text.end();
//     std::unordered_map<std::string, size_t> all_texts; 


//     while(first_word != end_text){
//         while((! isalpha(*first_word) || *first_word == ' ') && first_word != m_text.end()){
//             ++first_word;
//         }

//         end_word = first_word;
        
//         while(isalpha(*end_word)  && end_word != m_text.end()){
//             ++end_word;
//         }
 
//         fillMap(all_texts, first_word , end_word);
//         first_word = end_word;
//     } 

//     return all_texts;
// }

// void se::StringSplit::fillMap(WordsMap& seperated_text, StrIterator first_word ,StrIterator end_word )const
// {    
//     std::string word = std::string(first_word,end_word); 
//     std::unordered_map<std::string, size_t>::const_iterator it = seperated_text.find(word);
    
//     if(it == seperated_text.end()){
//         seperated_text.insert({word, 1});
//     } else {
//         seperated_text[word]++;
//     }
// }

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

// void se::StringSplit::fillMap(WordsMap& allWords, const std::string& word)const
// {    
//     auto it = allWords.find(word);
    
//     if(it == allWords.end()){
//         allWords.insert({word, 1});
//     } else {
//         allWords[word]++;
//     }
// }