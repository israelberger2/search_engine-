#include "safe_limit_counter.hpp"


se::SafeLimitCounter::SafeLimitCounter(int limit)
: m_limit(limit)
, m_count(0)
{}

void se::SafeLimitCounter::decrement()
{
    --m_count;
}

void se::SafeLimitCounter::jumpToLimit()
{
    m_count.store(m_limit.load()); 
}

bool se::SafeLimitCounter::CheckLimitAndIncrement()
{ 
    ++ m_count;
    
    return m_count <= m_limit ? true : false;  
}
 