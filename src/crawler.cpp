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
: m_inserter(updater)
, m_unvisited_links(scaner)
, m_unique_links()
, m_threads()
, m_limitScans(Config::getNumScans() + 1)
, m_countForFlash(Config::getNumThreads())
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

void Crawler::close()
{  
  m_limitScans.jumpToLimit();
  m_threads.makeJoin();
}

void Crawler::process_link()
{  
  std::string current_url;
  while(true){ 
    // std::cout << "tread id...................: " << std::this_thread::get_id() << '\n';
                    
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
 
    std::pair<std::unordered_map<std::string, int>, Map> result = 
    parser.result_parser(current_url);

    std::unordered_map<std::string, int>& linksList = result.first;
    
    fill_queue(linksList);
    m_inserter.fill(result, current_url);
    
  }  
   
  if(! m_countForFlash.CheckLimitAndIncrement()){    
    m_inserter.bufferFlush();
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
 