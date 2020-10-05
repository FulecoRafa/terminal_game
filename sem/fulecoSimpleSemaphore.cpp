#include "fulecoSimpleSemaphore.h"

namespace fulss{
  
// Keeps a list of all semaphores in structure name:{first:max, second:value}
std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> sem_collection;
std::unordered_map<std::string, bool> mutex_collection;

/************
 * SEMAPHORES
 * *********/

// Creates a semaphore with a defined number of slots.
bool create_semaphore(std::string name, unsigned int slots){
  if(fulss::sem_collection.find(name) != fulss::sem_collection.end()) return false;
  else{
    fulss::sem_collection[name].first = slots;
    fulss::sem_collection[name].second = slots;
    return true;
  }
}

// Removes a semaphore if it exists.
bool remove_semaphore(std::string name){
  if(fulss::sem_collection.find(name) == fulss::sem_collection.end()) return false;
  else{
    fulss::sem_collection.erase(name);
    return true;
  }
}

// Check if semaphore is available and wait for it. Decreases availability.
bool wait(std::string name){
  if(fulss::sem_collection.find(name) == fulss::sem_collection.end()) return false;
  while(fulss::sem_collection[name].second == 0);
  fulss::sem_collection[name].second--;
  return true;
}

// Releases availability for semaphore.
bool uncommit(std::string name){
  if(fulss::sem_collection.find(name) == fulss::sem_collection.end()) return false;
  fulss::sem_collection[name].second = fulss::sem_collection[name].second + 1 > fulss::sem_collection[name].first? fulss::sem_collection[name].first : fulss::sem_collection[name].second + 1;
  return true;
}

/********
 * MUTEX
 * *****/

// Creates a mutex.
bool create_mutex(std::string name){
  if(fulss::mutex_collection.find(name) != fulss::mutex_collection.end()) return false;
  else{
    fulss::mutex_collection[name] = true;
    return true;
  }
}

// Removes mutex.
bool remove_mutex(std::string name){
  if(fulss::mutex_collection.find(name) == fulss::mutex_collection.end()) return false;
  else{
    fulss::mutex_collection.erase(name);
    return true;
  }
}

// Locks mutex.
bool lock(std::string name){
  if(fulss::mutex_collection.find(name) == fulss::mutex_collection.end()) return false;
  while(!fulss::mutex_collection[name]);
  fulss::mutex_collection[name] = false;
  return true;
}

// Unlocks mutex.
bool unlock(std::string name){
  if(fulss::mutex_collection.find(name) == fulss::mutex_collection.end()) return false;
  fulss::mutex_collection[name] = true;
  return true;
}

}