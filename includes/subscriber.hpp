#ifndef SUBSCRIBER_HPP 
#define SUBSCRIBER_HPP 
  

namespace se{
    
class Subscriber
{
public:
    virtual ~Subscriber() = default;
    
    virtual void unsubscribe() = 0;
    virtual void update() = 0;

};

} //se
#endif
