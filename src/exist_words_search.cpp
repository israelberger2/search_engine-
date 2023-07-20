#include <climits>
#include <algorithm>
 
#include "exist_words_search.hpp"


namespace se{

ExistWordsSearch::ExistWordsSearch(const Database& database)
: m_database(database)
{}

pairVector ExistWordsSearch::get_links(const StringsVector& query)const
{    
    std::string first_word = query.front();
    pairVector current_links = m_database.get_related_links(first_word);

    StringsVector related_links;

    for(const auto& word : query){

        update_list(current_links , word);

        if(current_links.empty()){
            break;        
        }
    }

    return current_links;
}

void ExistWordsSearch::update_list(pairVector& current_links,const std::string& word)const
{
    pairVector related_links = m_database.get_related_links(word);

    if(related_links.empty()){
        current_links.clear();
        return;
    }

    pairVector updated_links;

    auto it = current_links.begin();
    auto itEnd = current_links.end();
    auto re_links_end = related_links.end();

    while(it != itEnd){

        auto sign = std::find_if(related_links.begin(), re_links_end,
        [&it](const auto& p) { return p.first == it->first; });
        if (sign != re_links_end) {
            updated_links.push_back(*it);
        }
        
        ++ it;
    }
    
    if(! noFind(updated_links, current_links)){
        return;
    }

    current_links = updated_links;
}
 
bool ExistWordsSearch::noFind(const pairVector& updated_links,pairVector& current_links)const
{
    if(updated_links.empty()){
        current_links.clear();
        return false;
    } 

    return true;
}

} // namespace se
