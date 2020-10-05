#ifndef FULECO_SIMPLE_SEMAPHORE
#define FULECO_SIMPLE_SEMAPHORE

#include <string>
#include <unordered_map>

namespace fulss{

  // Semaphore

  bool create_semaphore(std::string name, unsigned int slots);
  bool remove_semaphore(std::string name);
  bool wait(std::string name);
  bool uncommit(std::string name);

  // Mutex

  bool create_mutex(std::string name);
  bool remove_mutex(std::string name);
  bool lock(std::string name);
  bool unlock(std::string name);
}

#endif