#include <utility>
#include <unordered_map>
#include <iostream>

#include "crawler.hpp"
#include "parser_html.hpp"
#include "extract_html.hpp"
#include "se_exceptions.hpp"
#include "configuration.hpp"
#include "reg_algo_links_maintenance.hpp"


namespace se{

Crawler::Crawler(Updater& updater)
: m_inserter(updater)
, m_unvisited_links()
, m_unique_links()
, m_threads()
, m_borderManager()
{}

void Crawler::insert_src_url()
{
  std::vector<std::string> urls = Config::getAddresses();

  for(const auto& url : urls){
    m_unvisited_links.enqueue(url);
    m_unique_links.insert(url);
  }
}

void Crawler::crawl()
{
  insert_src_url();
  m_threads.run_threads([this](){process_link();});
}

void Crawler::close()
{
  m_borderManager.comeToLimit();
  m_threads.makeJoin();
}

void Crawler::process_link()
{
  std::string current_url;
  while(true){    
    if(! m_borderManager.check_limit()){ 
      m_unvisited_links.setStatus();
      m_unvisited_links.notify();
      break;
    }
    
    bool status = m_unvisited_links.dequeue(current_url, [](size_t sleepingThreads){
      return Config::getNumThreads() < sleepingThreads;
    });

    if(!status){
      break;
    }

    std::string html;
    try{
      html = extract_html(current_url);
    } catch (const HtmlExcaption& error){
      m_borderManager.decreaseNumScan();
      continue;
    }
    
    RegularAlgo_LinksMaintenance algorithm{};
    ParserHtml parser(html,algorithm);
 
    std::pair<std::unordered_map<std::string, int>, Map> result = 
    parser.result_parser(current_url);

    std::unordered_map<std::string, int>& linksList = result.first;

    fill_queue(linksList);
    m_inserter.fill(result, current_url);
  }  
  //m_inserter.bufferFlush();
}

bool Crawler::queueIsEmpty()const
{
  return m_unvisited_links.empty();
}

void Crawler::fill_queue(const std::unordered_map<std::string, int>& result_links) 
{
  for(auto& link : result_links){
    if(m_unique_links.insert(link.first) && !link.first.empty()){
      m_unvisited_links.enqueue(link.first);
    }
  }
}

// void Crawler::fill_queue(const std::vector<std::string>& result_links) 
// {
//   for(auto& link : result_links){
//     if(m_unique_links.insert(link) && !link.empty()){
//       m_unvisited_links.enqueue(link);
//     }
//   }
// }

} //namespace se
 