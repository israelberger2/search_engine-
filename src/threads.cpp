#include  "threads.hpp"
#include "configuration.hpp"
 
 
namespace se{

Threads::Threads()
: m_threads()
{}

Threads::~Threads()
{
    for(auto& t : m_threads){
        if(t.joinable()){
            t.join();
        };
    }         
}

void Threads::makeJoin()
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

} // namespace se
