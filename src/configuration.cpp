#include <fstream>

#include "json.hpp"
#include "se_exceptions.hpp"
#include "configuration.hpp"


namespace se{   

Config::Config()
{
    std::ifstream input_file("includes/configuration.json");

    if (!input_file.is_open()){
        throw OpenFileError("ERROR:: not opem file");
    }

    fill_dataMembers(input_file);
}

void Config::fill_dataMembers(std::ifstream& stream)
{
    nlohmann::json js; 
    stream >> js;  

    m_sql_password = js["sql_password"];
    m_sql_username = js["sql_username"];
    m_sql_schema = js["sql_schema"];
    m_sql_connectionString = js["sql_connectionString"];
    m_numScans = js["scans"];
    m_scanType = js["scanType"];
    m_numThreads = js["threads"];
    m_startOfLink = js["StartOfLink"];
    m_address = js["addresses"];
    m_clientType = js["clientType"];
    m_sortType = js["sortType"]; 
    m_lengthResult = js["lengthResult"];
    m_linksMountForPagerank = js["linksMountForPagerank"];    
    m_port = js["port"];   
}

const Config& Config::getInstance()
{ 
    static Config config;
    return config;
}

std::string Config::getSqlUsername()
{
    return Config::getInstance().m_sql_username;
}

std::string Config::getSqlPassword()
{
    return Config::getInstance().m_sql_password;
}

std::string Config::getSqlSchema()
{
    return Config::getInstance().m_sql_schema;
}

std::string Config::getSqlConnectionString()
{
    return Config::getInstance().m_sql_connectionString;
}

int Config::getNumScans()
{
    return Config::getInstance().m_numScans;
}

std::string Config::getScanType()
{
    return Config::getInstance().m_scanType;
}

size_t Config::getLengthResult()
{
    return Config::getInstance().m_lengthResult;
}

size_t Config::getNumThreads()
{
    return Config::getInstance().m_numThreads;
}
 
std::vector<std::string> Config::getAddresses()
{
    return Config::getInstance().m_address;
}

std::string Config::getClientType()
{
    return Config::getInstance().m_clientType;
}

std::string Config::getSortType()
{
    return Config::getInstance().m_sortType;
}

size_t Config::getLinksMountForPagerank()
{
    return Config::getInstance().m_linksMountForPagerank;
}

uint16_t Config::getPort()
{
    return Config::getInstance().m_port;
}

std::string Config::getStartOfLink()
{
    return Config::getInstance().m_startOfLink;
}

} // namespace se
