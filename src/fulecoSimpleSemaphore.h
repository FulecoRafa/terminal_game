#ifndef FULECO_SIMPLE_SEMAPHORE
#define FULECO_SIMPLE_SEMAPHORE

#include <string>
#include <unordered_map>
#include <atomic>

namespace fulss{

  // Semaphore

  bool create_semaphore(std::string name, unsigned int slots);
  bool remove_semaphore(std::string name);
  bool down(std::string name);
  bool up(std::string name);

  // Mutex

  bool create_mutex(std::string name);
  bool remove_mutex(std::string name);
  bool lock(std::string name);
  bool unlock(std::string name);
}

#endif