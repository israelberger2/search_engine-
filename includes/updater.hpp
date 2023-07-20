#ifndef C_INSERTIONER_HPP
#define C_INSERTIONER_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <shared_mutex>

#include "publisher.hpp"
#include "safe_unordered_map.hpp"
#include "word_links.hpp"
#include "graph_data.hpp"


namespace se{

using Map = std::unordered_map<std::string, int>;
 
class Updater
{
public:
    Updater(size_t mount, Publisher& publisher, db::GraphData& graph, db::WordLinks& words);
    ~Updater() = default;
    Updater(const Updater&) = default;
    Updater& operator= (const Updater&) = default;
    
    void fill(std::pair<Map, Map>& resCrewl ,const std::string& url);
    void bufferFlush();
 
private:
    SafeUnorderedMap<std::string, std::pair<Map, Map>> m_buffer;
    size_t m_mount;
    Publisher& m_publisher;
    std::shared_mutex m_mtx;
    std::shared_mutex m_notMtx;
    db::GraphData& m_graphData;
    db::WordLinks& m_wordsData;
};

} // namespace se
#endif
 
// #ifndef C_INSERTIONER_HPP
// #define C_INSERTIONER_HPP

// #include <vector>
// #include <string>
// #include <unordered_map>
// #include <utility>
// #include <shared_mutex>

// #include "links_map_insertion.hpp"
// #include "indexer_insertion.hpp"
// #include "publisher.hpp"
// #include "safe_unordered_map.hpp"


// namespace se{

// using LinksVector = std::vector<std::string>;
// using WordsMap = std::unordered_map<std::string, size_t>;

// class Updater
// {
// public:
//     Updater(LinksMamInsertion& linkMap, IndexerInsertion& indexer, size_t mount, Publisher& publisher);
//     ~Updater() = default;
//     Updater(const Updater&) = default;
//     Updater& operator= (const Updater&) = default;
    
//     void fill(std::pair<LinksVector, WordsMap>& resCrewl ,const std::string& url);
 
//     void bufferFlush();
 
// private:
//     IndexerInsertion& m_indexer;
//     SafeUnorderedMap<std::string, std::pair<LinksVector, WordsMap>> m_buffer;
//     LinksMamInsertion& m_linkMap;
//     size_t m_mount;
//     Publisher& m_publisher;
//     std::shared_mutex m_mtx;
//     std::shared_mutex  m_notMtx;
// };

// } // namespace se
// #endif
 