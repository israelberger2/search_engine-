#include <algorithm>
#include "publisher.hpp"
  

se::Publisher::Publisher()
: m_subscribers()
{}

void se::Publisher::notify()
{    
    for(auto subscriber : m_subscribers){
        subscriber->update();
    }
}

void se::Publisher::add(Subscriber* subscriber)
{
    m_subscribers.push_back(subscriber);
}

void se::Publisher::remove(Subscriber* subscriber)
{
    auto it = std::find(m_subscribers.begin(), m_subscribers.end(), subscriber);
	m_subscribers.erase(it);  
}
