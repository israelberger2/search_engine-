#include <iostream>
#include  <utility>

#include "search_engine.hpp"
#include "se_exceptions.hpp"
 

namespace se{

SearchEngine::SearchEngine(std::shared_ptr<db::Searcher> searcher, Client& client, Isorter& sorter)
: m_searcher(searcher)
, m_client(client)
, m_arranger(sorter)
{}

void SearchEngine::handle(size_t length)const
{
    while (true){
        try{
            std::vector<std::string> keywords = m_client.load_query();
            if(keywords.empty()){
                break;
            }

            std::vector<std::string> positive;
            std::vector<std::string> negative;
            if(! createQueriesVectors(positive, negative, keywords)){                
                continue;
            }
            
            std::vector<std::pair<std::string,int>> links =  m_searcher->search(positive, negative);
            m_arranger.sort_links(links , length);            
            
            if(links.size() > length){
                links.resize(length);
            }
             
            m_client.send_data(links);             
        } catch (const ServerSocketError& error){
            std::cout <<"a" << error.what();
            throw ServerSocketError(error.what());
        } catch (const DataError& error){
            std::cout << "b" << error.what() << "\n";
        } catch (const NetworkError& error){
            std::cout << "c" << error.what() << "\n";
        } 
    }
}

bool SearchEngine::createQueriesVectors(std::vector<std::string>& positive, std::vector<std::string>& negative, const std::vector<std::string>& input)const
{
    for(auto& str : input){
        if(str[0] != '-'){
            positive.push_back(str);
        } else if(str.length() > 3){
            negative.push_back(str.substr(1));
        }
    }

    return positive.empty() ? false : true;
}

} // namespace se
