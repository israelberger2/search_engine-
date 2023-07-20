#include <algorithm>
 
#include "unexist_words_search.hpp"

namespace se{

UnexistWordsSearch::UnexistWordsSearch(const Database& database)
: m_database(database)
{}

pairVector UnexistWordsSearch::get_links(const StringsVector& query)const 
{
    std::string first_word = query.front();
    pairVector current_links = m_database.get_related_links(first_word);
    
    auto it = query.begin() +1;
    auto itEnd = query.end();
 
    while(it != itEnd){
        std::string key = clear_word(*it);
        update_list(current_links, key);

        if(current_links.empty()){
            break;        
        }

        ++ it;
    }

    return current_links;   
}

void UnexistWordsSearch::update_list(pairVector& current_links,const std::string& word)const
{
    pairVector related_links = m_database.get_related_links(word);
   
    if(related_links.empty()){
        return;
    }

    pairVector updated_links;

    auto it = current_links.begin();
    auto itEnd = current_links.end();
    auto re_links_end = related_links.end();

     
    while(it != itEnd){

        auto sign = std::find_if(related_links.begin(), re_links_end,
        [&it](const auto& p) { return p.first == it->first; });
        if (sign == re_links_end) {
            updated_links.push_back(*it);
        }
        
        ++ it;
    }
 
    current_links = updated_links;
}

std::string UnexistWordsSearch::clear_word(const std::string& query)const
{
    std::string key = query.substr(1);

    return key;
}

} // namespace se