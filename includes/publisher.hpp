#ifndef publisher_HPP
#define publisher_HPP

#include <vector>
#include "subscriber.hpp"


namespace se{

class Publisher
{
public:
    Publisher();
    ~Publisher() = default;
    Publisher(const Publisher&) = default;
    Publisher& operator= (const Publisher&) = default;

    void notify();
    void add(Subscriber* subscriber);
    void remove(Subscriber* subscriber);

private:
    std::vector<Subscriber*> m_subscribers;
};

} // namespace se
#endif
