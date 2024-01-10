#include  <utility>
#include <iostream>

#include "search_engine.hpp"
#include "se_exceptions.hpp"
 

namespace se{

SearchEngine::SearchEngine(std::shared_ptr<db::Searcher> searcher, std::shared_ptr<Client> client, std::shared_ptr<Isorter> sorter)
: m_searcher(searcher)
, m_client(client)
, m_arranger(sorter)
{}

void SearchEngine::run(size_t length)const
{
    while (true){
        try{            
            std::vector<std::string> keywords = m_client->load_query();
             
            std::vector<std::string> positive;
            std::vector<std::string> negative;
            if(! createQueriesVectors(positive, negative, keywords)){                
                continue;
            }
            
            std::vector<std::pair<std::string,int>> links =  m_searcher->search(positive, negative);
            std::cout << "sizeee: " << links.size() << '\n';
            
            m_arranger->sort_links(links , length);            
            
            if(links.size() > length){
                links.resize(length);
            }
             
            m_client->send_data(links);             
        } catch (const SocketError& error){
            throw SocketError(error.what());
        } catch (const DataError& error){
            std::clog << error.what() << "\n";
        } catch (const NetworkError& error){
            std::cout << error.what() << "\n";
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
