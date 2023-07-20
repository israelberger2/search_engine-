#include <iostream>

#include "se_exceptions.hpp"
#include "link.hpp"


se::Link::Link(const std::string &url)
{
    init(url);
}

std::string se::Link::getDomain()const
{
    return m_domain;
}

std::string se::Link::getPath()const
{
    return m_path;
}

void se::Link::init(const std::string &url)
{
    try{    
    size_t instance1 = url.find('/');
    size_t instance2 = url.find('/', (instance1 + 2));
     
    m_path  = url.substr(instance2);
     
    m_domain = url.substr(0,instance2);
    if(m_domain.length() <= 3){
        throw se::InValidLink("ERROR: invalid link");
    }
    
    } catch(const std::out_of_range& error){
        throw se::InValidLink("ERROR: invalid link");
    }
}
