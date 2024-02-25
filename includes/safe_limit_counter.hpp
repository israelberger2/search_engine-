#ifndef SAFE_LIMIT_COUNTER_HPP 
#define SAFE_LIMIT_COUNTER_HPP 

#include <atomic>


namespace se {
 
class SafeLimitCounter {
public:
  explicit SafeLimitCounter(int limit);
  ~SafeLimitCounter() = default;
  SafeLimitCounter(const SafeLimitCounter&) = default;
  SafeLimitCounter& operator= (const SafeLimitCounter&) = default;

  bool CheckLimitAndIncrement();
  void decrement();
  void jumpToLimit();

private:
  int m_limit;
  std::atomic_int m_count;
}; 
 
} // namespace se

#endif
