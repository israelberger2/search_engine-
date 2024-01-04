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
    static int getNumScans();
    static std::string getScanType();
    static size_t getNumThreads();
    static std::vector<std::string> getAddresses();
    static size_t getLengthResult();
    static size_t getLinksMountForPagerank();
    static uint16_t getPort();
    static std::string getStartOfLink();
 
private:
    static const Config& getInstance(); 
    explicit Config(); 

    void fill_dataMembers(std::ifstream& stream);

private:
    std::string m_sql_username;
    std::string m_sql_password;
    std::string m_sql_schema;
    std::string m_sql_connectionString;
    int m_numScans;
    std::string m_scanType;
    size_t m_numThreads;
    std::vector<std::string> m_address;
    std::string m_startOfLink;
    size_t m_lengthResult;
    size_t m_linksMountForPagerank;
    uint16_t m_port;
};

} // namespace se
#endif