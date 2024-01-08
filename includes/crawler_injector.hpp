#ifndef CRAWLER_INJECTOR_HPP 
#define CRAWLER_INJECTOR_HPP 

#include <memory>
#include "crawler.hpp"


namespace se{
 
class Crawler_Injector
{
public:
    Crawler_Injector() = default;
    ~Crawler_Injector() = default;
    Crawler_Injector(const Crawler_Injector&) = default;
    Crawler_Injector& operator= (const Crawler_Injector&) = default;

    std::unique_ptr<Crawler> create()const;
};
 
} //neme
#endif
