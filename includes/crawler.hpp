#ifndef CRAWLER_HPP
#define CRAWLER_hpp

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "threads.hpp"
#include "bfs.hpp"
#include "safe_unordered_set.hpp"
#include "updater.hpp"
#include "safe_limit_counter.hpp"
#include "safe_scan.hpp"


namespace se{

class Crawler
{
public:
    explicit Crawler(Updater& updater, std::shared_ptr<SafeScan<std::string>> scaner);
    ~Crawler() = default;
    Crawler(const Crawler&) = delete;
    Crawler& operator= (const Crawler&) = delete;

    void crawl();
    void close();

private:
    void fill_queue(const std::unordered_map<std::string, int>& result_links);
    void process_link();
    bool queueIsEmpty()const;

    void insert_src_url();
  
private:
    Updater& m_inserter;
    std::shared_ptr<SafeScan<std::string>> m_unvisited_links;
    SafeUnorderedSet<std::string> m_unique_links;
    Threads m_threads;
    SafeLimitCounter m_limitScans;
    SafeLimitCounter m_countForFlash;
};

} // namespace se
#endif
