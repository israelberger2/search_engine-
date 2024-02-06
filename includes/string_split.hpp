#ifndef STRING_SPLIT_HPP 
#define STRING_SPLIT_HPP 
 
#include <string>
#include <unordered_map>


namespace se{
 
using WordsMap = std::unordered_map<std::string, int>;
using StrIterator = std::string::const_iterator;

class StringSplit
{
public:
    explicit StringSplit(std::string& htmt_text);
    ~StringSplit() = default;
    StringSplit(const StringSplit&) = default;
    StringSplit& operator= (const StringSplit&) = default;

    WordsMap parser();

private:
    std::string m_text;
};

} //namespace 
#endif
 