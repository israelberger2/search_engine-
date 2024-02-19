#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <utility>


namespace se{

class Client   
{
public:
    virtual ~Client() = default;

    virtual std::vector<std::string> load_query() = 0;
    virtual void send_data(const std::vector<std::pair<std::string, int>>& links)const = 0;
};
    
} // namespace se
#endif
