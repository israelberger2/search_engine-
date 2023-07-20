#include <functional>
 
#include "indexer.hpp"


namespace se{
    
Indexer::Indexer()
: m_safeMap()
{}

std::vector<std::pair<std::string, size_t>> Indexer::get_links(const std::string& key)const
{
    return m_safeMap.get_dada(key); 
}

bool Indexer::is_here(const std::string& data)const 
{
    return m_safeMap.is_here(data);
}

void Indexer::insert(const WordsMap& WordsMap, const std::string& url)  
{ 
    for(auto& [word , amount]: WordsMap){
        std::vector<std::pair<std::string, size_t>> newUrl = {{url, amount}};
         
        if(!m_safeMap.insert(word, newUrl)){
            auto key = word;
            std::function<void(std::vector<std::pair<std::string, size_t>>&)> func = 
            [url, word , amount](std::vector<std::pair<std::string, size_t>>& relatedLinks){
                relatedLinks.push_back({url, amount});
            };
            
            m_safeMap.update(func, key);
        }   
    }
}
 
size_t Indexer::size()const
{
    return m_safeMap.size();
}

} // namespace se
