#include <algorithm>
#include <iostream>

#include "exist_and_unexist_search.hpp"
#include "exist_words_search.hpp"
#include "unexist_words_search.hpp"


namespace se{

ExistAndUnexistSearch::ExistAndUnexistSearch(const Database& database)
: m_database(database)
{}

pairVector ExistAndUnexistSearch::get_links(const StringsVector& query)const 
{
    ExistWordsSearch exist_sercher(m_database);
    UnexistWordsSearch un_searcher(m_database);

    std::pair<std::vector<std::string>,std::vector<std::string>> res = query_for_searchers(query);

    StringsVector exist = res.first;
    StringsVector unexist = res.second;

    pairVector  exist_answer = exist_sercher.get_links(exist);
    pairVector  unexist_answer = un_searcher.get_links(unexist);

    pairVector result = links_list(exist_answer, unexist_answer);

    return result;
}

std::pair<StringsVector, StringsVector> ExistAndUnexistSearch::query_for_searchers(const StringsVector& query)const
{

    auto it = query.begin();
    auto endIt = query.end();
    StringsVector exist;
    StringsVector unexist;
    
    while(it != endIt){
        if((*it)[0] != '-'){
            unexist.push_back(*it);
            break;
        }

        ++ it;
    }

    it = query.begin();

    while(it != endIt){

        if((*it)[0] == '-'){
            unexist.push_back(*it);
        } else{
            exist.push_back(*it);
        }
        ++ it;
    }

    std::pair<StringsVector ,StringsVector> result = {exist, unexist};

    return result;
}

pairVector ExistAndUnexistSearch::links_list(const pairVector& exist_answer , const pairVector& unexist_answer)const
{
    auto first_exist = exist_answer.begin();
    auto end_exist = exist_answer.end();
    auto firstUnExist = unexist_answer.begin();
    auto endUnExist = unexist_answer.end();

    pairVector updated_links;
 
    while(first_exist != end_exist){
        auto sigen = std::find_if(firstUnExist ,endUnExist, 
        [&first_exist](const auto& p) {return p.first == first_exist->first;});
        if(sigen != endUnExist){
            updated_links.push_back(*first_exist);
        }
        ++ first_exist;
    }

    return updated_links;
}

} //namespace se
