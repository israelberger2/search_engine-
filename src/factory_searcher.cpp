#include <algorithm>

#include <factory_searcher.hpp>
#include "exist_words_search.hpp"
#include "unexist_words_search.hpp"
#include "exist_and_unexist_search.hpp"
 
 
namespace se{

std::unique_ptr<Searcher> FactorySearcher::creator(const std::vector<std::string>& input,const Database& database)
{
    auto it = std::find_if(input.begin(), input.end(), [](const std::string& link) { return link[0] == '-';});
    bool negative;

    if(it != input.end()){
        negative = true;
    }
    
    if(negative == true){
        if(exist_words(input) == true){
            std::unique_ptr<Searcher> exist_and_unexist_search = std::make_unique<ExistAndUnexistSearch>(database);
            return exist_and_unexist_search;
        } else {
            std::unique_ptr<Searcher> unexist = std::make_unique<UnexistWordsSearch>(database);
            return unexist;
        }
    } else {
        std::unique_ptr<Searcher> exist = std::make_unique<ExistWordsSearch>(database);
        return exist;
    }
}

bool FactorySearcher::exist_words(const std::vector<std::string>& input)
{
    int count  = 0;
    for(const auto& link : input){
        if(link[0] != '-'){
            ++ count;
        }

        if(count >= 2){
            return true;
        }
    }

    return false;
}

} // namespace se
