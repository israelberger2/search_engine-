#include "safe_limit_counter.hpp"
#include <iostream>

se::SafeLimitCounter::SafeLimitCounter(int limit)
: m_limit(limit)
, m_count(1)
{}

void se::SafeLimitCounter::decrement()
{
    --m_count;
}

void se::SafeLimitCounter::jumpToLimit()
{
    m_count.store(m_limit); 
}

bool se::SafeLimitCounter::CheckLimitAndIncrement()
{         
    return  m_count.fetch_add(1) < m_limit;
}
 