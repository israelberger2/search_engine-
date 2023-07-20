#ifndef LINK_HPP 
#define LINK_HPP 

#include <string>

 
namespace se{
 
class Link
{
public:
    explicit Link(const std::string& url);
    ~Link() = default;
    Link(const Link&) = default;
    Link& operator= (const Link&) = default;
    
    std::string getDomain()const;
    std::string getPath()const;

private:
    void init(const std::string& url);

private:   
    std::string m_domain;
    std::string m_path;
};
 
} //se
#endif
