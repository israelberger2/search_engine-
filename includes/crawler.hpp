#ifndef CRAWLER_HPP
#define CRAWLER_hpp

#include <string>
#include <vector>
#include <functional>

#include "threads.hpp"
#include "safe_queue.hpp"
#include "safe_unordered_set.hpp"
#include "border_manager.hpp"
#include "updater.hpp"


namespace se{

class Crawler
{
public:
    explicit Crawler(Updater& updater);
    ~Crawler() = default;
    Crawler(const Crawler&) = delete;
    Crawler& operator= (const Crawler&) = delete;

    void crawl();
    void close();

private:
    //void fill_queue(const std::vector<std::string>& result_links); 
    void fill_queue(const std::unordered_map<std::string, int>& result_links);
    void process_link();
    bool queueIsEmpty()const;

    void insert_src_url();
  
private:
    Updater& m_inserter;
    SafeQueue<std::string> m_unvisited_links;
    SafeUnorderedSet<std::string> m_unique_links;
    Threads m_threads;
    BorderManager m_borderManager;
};

} // namespace se
#endif
