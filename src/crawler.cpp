#include <utility>
#include <unordered_map>
 
#include "crawler.hpp"
#include "parser_html.hpp"
#include "extract_html.hpp"
#include "se_exceptions.hpp"
#include "configuration.hpp"

#include <iostream>
#include <thread>

namespace se{

Crawler::Crawler(Updater& updater, std::shared_ptr<SafeScan<std::string>> scaner)
: m_updater(updater)
, m_unvisited_links(scaner)
, m_unique_links()
, m_limitScans(Config::getNumScans() + 1)
, m_countForFlash(Config::getNumThreads())
, m_threads()
{}

void Crawler::insert_src_url()
{
  std::vector<std::string> urls = Config::getAddresses();

  for(const auto& url : urls){
    m_unvisited_links->add(url);
    m_unique_links.insert(url);
  }
}

void Crawler::crawl()
{
  insert_src_url();
  m_threads.run_threads([this](){process_link();});
}

void Crawler::process_link()
{  
  std::string current_url;
  while(true){                     
    if(! m_limitScans.CheckLimitAndIncrement()){       
      m_unvisited_links->stop();
      break;
    }
    
    bool status = m_unvisited_links->get(current_url, [](size_t sleepingThreads){
      return Config::getNumThreads() > sleepingThreads;
    });

    if(!status){
      break;
    }
    
    std::string html;
    try{
      html = extract_html(current_url);
    } catch (const HtmlExcaption& error){
      m_limitScans.decrement();      
      continue;
    }
    
    ParserHtml parser(html);
 
    std::pair<Map, Map> result = 
    parser.result_parser(current_url);
    if(result.first.empty() && result.second.empty()){
      continue;
    }
    std::unordered_map<std::string, int>& linksList = result.first;
    
    fill_queue(linksList);
    m_updater.fill(result, current_url);
    
  }  
   
  if(! m_countForFlash.CheckLimitAndIncrement()){    
    m_updater.bufferFlush();
  }
  
}

bool Crawler::queueIsEmpty()const
{
  return m_unvisited_links->empty();
}

void Crawler::fill_queue(const std::unordered_map<std::string, int>& result_links) 
{
  for(auto& link : result_links){
    if(m_unique_links.insert(link.first) && !link.first.empty()){
      m_unvisited_links->add(link.first);
    }
  }
}

} //namespace se
 