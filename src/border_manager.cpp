#include <mutex>

#include "border_manager.hpp"
#include "configuration.hpp"
 
 
se::BorderManager::BorderManager()
: m_mtx()
, m_limit(Config::getNumScans())
, m_numScan(0)
{}

void se::BorderManager::decreaseNumScan()
{
    --m_numScan;
}

void se::BorderManager::comeToLimit()
{
    m_numScan = m_limit;
}

bool se::BorderManager::check_limit()
{
    std::unique_lock<std::shared_mutex> lock(m_mtx);

    if(m_numScan >= m_limit){
        return false;
    }

    ++m_numScan;
    return true;  
}
 