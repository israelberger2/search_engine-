#ifndef THREADS_HPP
#define THREADS_HPP

#include <functional>
#include <vector>
#include <thread>


namespace se{   

class Threads
{
public:
    Threads();
    ~Threads(); 
    Threads(const Threads&) = delete;
    Threads& operator= (const Threads&) = delete;

    void run_threads(std::function<void()> func);
    void wait_to_threads();
 
private:
    std::vector<std::thread> m_threads;
};

} // namespace se
#endif
