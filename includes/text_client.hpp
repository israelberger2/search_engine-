#ifndef TextClient_HPP
#define TextClient_HPP

#include <string>
#include <vector>

#include "client.hpp"


namespace se{

class TextClient : public Client
{
public:
    TextClient() = default;
    ~TextClient() = default;
    TextClient(const TextClient&) = default;
    TextClient& operator= (const TextClient&) = default;

    std::vector<std::string> load_query()override;
    void send_data(const std::vector<std::pair<std::string, int>>& links)const;

private:
    bool is_valide_input(const std::string& input)const;
    std::vector<std::string> get_substrings(const std::string& input)const;
};
    
} // namespace se
#endif
 