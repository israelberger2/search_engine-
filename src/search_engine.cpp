// #include <iostream>
// #include <sstream>
// #include  <utility>

// #include "search_engine.hpp"
// #include "factory_searcher.hpp"
// #include "se_exceptions.hpp"
// #include "regular_sorter.hpp"

// namespace se{

// SearchEngine::SearchEngine(IndexerGet& word, LinksMapGet& links, Client& client, Isorter& sorter)

// : m_database(Database::getInstance(word, links))
// , m_client(client)
// , m_arranger(sorter)
// {}

// void SearchEngine::handle(size_t length)const
// {
//     while (true){
//         try{
//             std::vector<std::string> keywords = m_client.load_query();
//             if(keywords.empty()){
//                 break;
//             }
             
//             std::unique_ptr<Searcher> searcher =  FactorySearcher::creator(keywords,m_database);
//             std::vector<std::pair<std::string, size_t>> links = searcher->get_links(keywords);
              
//             m_arranger.sort_links(links , length);
             
//             if(links.size() > length){
//                 links.resize(length);
//             }
             
//             m_client.send_data(links); 

//         } catch (const ServerSocketError& error){
//             std::cout << error.what();
//             throw ServerSocketError(error.what());
//         } catch (const DataError& error){
//             std::cout << error.what() << "\n";
//         } catch (const NetworkError& error){
//             std::cout << error.what() << "\n";
//         } 
//     }
// }

// void SearchEngine::opening_message()const
// {
//   size_t num_links = m_database.get_links_size();
//   size_t num_word = m_database.get_words_size();
  
//   std::clog << "welcome to the search engine: " << num_links <<
//   " links and " << num_word << " search words\n";
// }

// } // namespace se


#include <iostream>
#include <sstream>
#include  <utility>

#include "search_engine.hpp"
#include "factory_searcher.hpp"
#include "se_exceptions.hpp"
#include "regular_sorter.hpp"

namespace se{

SearchEngine::SearchEngine(IndexerGet& word, LinksMapGet& links, Client& client, Isorter& sorter)

: m_database(Database::getInstance(word, links))
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
             
            // std::unique_ptr<Searcher> searcher =  FactorySearcher::creator(keywords,m_database);
             std::vector<std::pair<std::string, size_t>> links{};// = searcher->get_links(keywords);
              
            m_arranger.sort_links(links , length);
             
            if(links.size() > length){
                links.resize(length);
            }
             
            m_client.send_data(links); 

        } catch (const ServerSocketError& error){
            std::cout << error.what();
            throw ServerSocketError(error.what());
        } catch (const DataError& error){
            std::cout << error.what() << "\n";
        } catch (const NetworkError& error){
            std::cout << error.what() << "\n";
        } 
    }
}

void SearchEngine::opening_message()const
{
  size_t num_links = m_database.get_links_size();
  size_t num_word = m_database.get_words_size();
  
  std::clog << "welcome to the search engine: " << num_links <<
  " links and " << num_word << " search words\n";
}

} // namespace se
