#ifndef STRING_SPLIT_HPP 
#define STRING_SPLIT_HPP 
 
#include <string>
#include <unordered_map>


namespace se{
 
using WordsMap = std::unordered_map<std::string, int>;
 
WordsMap split(std::string& html_text);

} //namespace 
#endif
 