#include "json.hpp"
#include <fstream>

#include "se_exceptions.hpp"
#include "configuration.hpp"


namespace se{   

Config::Config()
{
    std::ifstream input_file("configuration.json");

    if (!input_file.is_open()){
        throw OpenFileError("ERROR:: not opem file");
    }

    fill_dataMembers(input_file);
}

void Config::fill_dataMembers(std::ifstream& stream)
{
    nlohmann::json js; 
    stream >> js;  

    m_numScans = js["scans"];
    m_numThreads = js["threads"];
    m_bounded = js["isBounded"];
    m_address = js["addresses"];
    m_lengthResult = js["lengthResult"];
}

const Config& Config::getInstance()
{ 
    static Config config;
    return config;
} 

size_t Config::getNumScans()
{
    return Config::getInstance().m_numScans;
}

size_t Config::getLengthResult()
{
    return Config::getInstance().m_lengthResult;
}

size_t Config::getNumThreads()
{
    return Config::getInstance().m_numThreads;
}

bool Config::getBounded()
{
    return Config::getInstance().m_bounded;
}

std::vector<std::string> Config::getAddresses()
{
    return Config::getInstance().m_address;
}

} // namespace se
