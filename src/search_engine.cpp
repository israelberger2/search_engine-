#include <iostream>

#include "search_engine.hpp"
#include "se_exceptions.hpp"
 

namespace se{

SearchEngine::SearchEngine(std::shared_ptr<db::Searcher> searcher, std::shared_ptr<Client> client, std::shared_ptr<Sorter> Sorter)
: m_searcher(searcher)
, m_client(client)
, m_sorter(Sorter)
{}

void SearchEngine::run(size_t length)const
{
    while (true){
        try{            
            std::vector<std::string> keywords = m_client->load_query();
             
           auto queriesVectors = createQueriesVectors(keywords);
           
            if(queriesVectors.first.empty()){                
                continue;
            }
            
            std::vector<std::pair<std::string,int>> links =  m_searcher->search(queriesVectors.first, queriesVectors.second);
             
            m_sorter->sort_links(links , length);            
            
            if(links.size() > length){
                links.resize(length);
            }
             
            m_client->send_data(links);             
        } catch (const SocketError& error){
            std::clog  << error.what() << "\n";
            break;
        } catch (const DataError& error){
            std::clog << error.what() << "\n";
        } catch (const NetworkError& error){
            std::cout << error.what() << "\n";
        } catch(const Exit& e){
            break;            
        }
    }
}

Parsed_query SearchEngine::createQueriesVectors(const std::vector<std::string>& input)const
{
    std::vector<std::string> positive;
    std::vector<std::string> negative;

    for(auto& str : input){
        if(str[0] != '-'){
            positive.push_back(str);
        } else if(str.length() > 3){
            negative.push_back(str.substr(1));
        }
    }

    return Parsed_query{positive, negative};
}

} // namespace se
