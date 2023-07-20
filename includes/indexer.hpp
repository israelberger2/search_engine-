#ifndef INDEXER_HPP
#define INDEXER_HPP

#include <string>
#include <vector>
 
#include "indexer_insertion.hpp"
#include "indexer_get.hpp"
#include "safe_unordered_map.hpp"


namespace se{

using PairsVector = std::vector<std::pair<std::string, size_t>>;
using WordsMap = std::unordered_map<std::string, size_t>;
using StrIterator = std::string::const_iterator;

class Indexer : public IndexerInsertion, public IndexerGet
{
public:
    Indexer();
    Indexer(const Indexer&) = default;
    ~Indexer() = default;
    Indexer& operator= (const Indexer&) = default;

    std::vector<std::pair<std::string, size_t>> get_links(const std::string& key)const override;
    bool is_here(const std::string& data)const override;
    void insert(const WordsMap& WordsMap, const std::string& url)override;

    size_t size()const override;
    
private:
    SafeUnorderedMap<std::string, PairsVector> m_safeMap;
};

} // namespace se
#endif
