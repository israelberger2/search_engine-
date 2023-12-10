#ifndef PARSER_HTML_hpp
#define PARSER_HTML_hpp

#include "gumbo.h"

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "link_maintenance_manager.hpp"


namespace se{

using WordsMap = std::unordered_map<std::string, int>;

class ParserHtml
{
public:
    explicit ParserHtml(const std::string& html);
    ~ParserHtml() = default;
    ParserHtml(const ParserHtml&) = default;
    ParserHtml& operator= (const ParserHtml&) = default;

    std::pair<std::unordered_map<std::string, int>, WordsMap> result_parser(const std::string& url);
 
private:
    std::string cleantext(GumboNode* node)const;
    std::string get_text()const;
    std::vector<std::string> get_links();
    std::unordered_map<std::string, int> convertToMap(const std::vector<std::string>& links)const;


private:
    std::string m_html;
};

} // namespace se
#endif
