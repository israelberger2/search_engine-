#ifndef UPDATER_HPP
#define UPDATER_HPP

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
    explicit Updater(Publisher& publisher, db::GraphData& graph, db::WordLinks& words);
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
    db::GraphData& m_graphData;
    db::WordLinks& m_wordsData;
};

} // namespace se
#endif
 