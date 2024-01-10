#ifndef CRAWLER_INJECTOR_HPP 
#define CRAWLER_INJECTOR_HPP 

#include "safe_scores_map.hpp"
#include "crawler.hpp"
#include "mysql_links_rank_manager.hpp"
#include "updater.hpp"
#include "mysql_graph_data.hpp"
#include "mysql_word_links.hpp"


namespace se{
 
class Crawler_Injector
{
public:
    Crawler_Injector(SafeScoresPointer& scores);
    ~Crawler_Injector() = default;
    Crawler_Injector(const Crawler_Injector&) = default;
    Crawler_Injector& operator= (const Crawler_Injector&) = default;

    Crawler create();
private:
    db::MysqlLinksRankManager m_rankManager;
    Publisher m_publisher;
    db::MysqlGraphData m_graph;
    db::MysqlWordLinks m_wordLinks;
    Updater m_updater;
};
 
} //neme
#endif
