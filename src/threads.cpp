#include "threads.hpp"
#include "configuration.hpp"
#include <iostream>

namespace se{

Threads::Threads()
: m_threads()
{}

Threads::~Threads()
{
    for(auto& t : m_threads){
        if(t.joinable()){
            t.join();
        }
    }
}
         
void Threads::run_threads(std::function<void()> func)
{
    size_t numThreads = Config::getNumThreads();
     
    for(size_t i = 0; i < numThreads; ++i){
        m_threads.emplace_back(func);
    }
}

void Threads::wait_to_threads()
{    
    for(auto& t : m_threads){
        if(t.joinable()){            
            t.join();
        }
    }    
}

} // namespace se
