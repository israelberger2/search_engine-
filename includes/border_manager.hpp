#ifndef BORDER_MANAGER_HPP
#define BORDER_MANAGER_HPP 

#include <shared_mutex>


namespace se{

class BorderManager
{
public:
  BorderManager();
  ~BorderManager() = default;
  BorderManager(const BorderManager&) = default;
  BorderManager& operator= (const BorderManager&) = default;

  bool check_limit();
  void decreaseNumScan();
  void comeToLimit();

private:
  std::shared_mutex m_mtx;  
  size_t m_limit;
  size_t m_numScan;
}; 

} //namespace se
#endif
