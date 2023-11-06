#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <vector>
#include <string>
 

namespace se{

class Config
{
public:
    Config(const Config&) = delete;
    Config& operator= (const Config&) = delete;
    ~Config() = default;
    
    static std::string getSqlUsername();
    static std::string getSqlPassword();
    static std::string getSqlSchema();
    static std::string getSqlConnectionString();
    static size_t getNumScans();
    static size_t getNumThreads();
    static bool getBounded();
    static std::vector<std::string> getAddresses();
    static size_t getLengthResult();
    static size_t getLinksMountForPagerank();
    static uint16_t getPort();
 
private:
    static const Config& getInstance(); 
    explicit Config(); 

    void fill_dataMembers(std::ifstream& stream);

private:
    std::string m_sql_username;
    std::string m_sql_password;
    std::string m_sql_schema;
    std::string m_sql_connectionString;
    size_t m_numScans;
    size_t m_numThreads;
    bool m_bounded;
    std::vector<std::string> m_address;
    size_t m_lengthResult;
    size_t m_linksMountForPagerank;
    uint16_t m_port;
};

} // namespace se
#endif