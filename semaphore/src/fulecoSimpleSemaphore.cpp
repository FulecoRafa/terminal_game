#include "fulecoSimpleSemaphore.h"
#include <cstdio>

namespace fulss {
  class Sem_data {
    public:
    std::atomic<unsigned int> value;
    unsigned int max;
    std::condition_variable cv;

    Sem_data() {
      this->lock = std::unique_lock<std::mutex>(this->mtx);
    }

    void operator=(unsigned int v) {
      this->max = v;
      this->value = v;
    }

    void down() {
      this->value--;
    }

    void up() {
      this->value = (this->value + 1 > this->max) ? (unsigned int) this->max : this->value + 1;
    }

    bool locked() {
      return this->value == 0;
    }

    void sleep() {
      this->cv.wait(this->lock);
    }

    void wakeup() {
      this->cv.notify_one();
    }

    private:
    std::mutex mtx;
    std::unique_lock<std::mutex> lock;
  };

  class Mtx_data {
    public:
    std::atomic<bool> value{};
    std::condition_variable cv;

    Mtx_data() {
      this->value = true;
      this->lck = std::unique_lock<std::mutex>(this->mtx);
    }

    void operator=(bool v) {
      this->value = v;
    }

    void lock() {
      this->value = false;
    }

    void unlock() {
      this->value = true;
    }

    bool locked() {
      return !this->value;
    }

    void sleep() {
      this->cv.wait(this->lck);
    }

    void wakeup() {
      this->cv.notify_one();
    }

    private:
    std::mutex mtx;
    std::unique_lock<std::mutex> lck;
  };

// Keeps a list of all semaphores in structure name:{first:max, second:value}
  std::unordered_map<std::string, fulss::Sem_data> sem_collection;
  std::unordered_map<std::string, fulss::Mtx_data> mutex_collection;

/************
 * SEMAPHORES
 * *********/

// Creates a semaphore with a defined number of slots.
  bool create_semaphore(std::string name, unsigned int slots) {
    if (fulss::sem_collection.find(name) != fulss::sem_collection.end()) return false;
    else {
      fulss::sem_collection[name] = slots;
      return true;
    }
  }

// Removes a semaphore if it exists.
  bool remove_semaphore(std::string name) {
    if (fulss::sem_collection.find(name) == fulss::sem_collection.end()) return false;
    else {
      fulss::sem_collection.erase(name);
      return true;
    }
  }

// Check if semaphore is available and wait for it. Decreases availability.
  bool down(std::string name) {
    if (fulss::sem_collection.find(name) == fulss::sem_collection.end()) return false;
    while (fulss::sem_collection[name].locked()) {
      fulss::sem_collection[name].sleep();
    }
    fulss::sem_collection[name].down();
    return true;
  }

// Releases availability for semaphore.
  bool up(std::string name) {
    if (fulss::sem_collection.find(name) == fulss::sem_collection.end()) return false;
    fulss::sem_collection[name].up();
    fulss::sem_collection[name].wakeup();
    return true;
  }

/********
 * MUTEX
 * *****/

// Creates a mutex.
  bool create_mutex(std::string name) {
    if (fulss::mutex_collection.find(name) != fulss::mutex_collection.end()) return false;
    else {
      fulss::mutex_collection[name] = true;
      return true;
    }
  }

// Removes mutex.
  bool remove_mutex(std::string name) {
    if (fulss::mutex_collection.find(name) == fulss::mutex_collection.end()) return false;
    else {
      fulss::mutex_collection.erase(name);
      return true;
    }
  }

// Locks mutex.
  bool lock(std::string name) {
    if (fulss::mutex_collection.empty()) return false;
    if (!fulss::mutex_collection.count(name)) return false;
    while (fulss::mutex_collection[name].locked()) fulss::mutex_collection[name].sleep();
    fulss::mutex_collection[name].lock();
    return true;
  }

// Unlocks mutex.
  bool unlock(std::string name) {
    if (fulss::mutex_collection.empty()) return false;
    if (!fulss::mutex_collection.count(name)) return false;
    fulss::mutex_collection[name].unlock();
    fulss::mutex_collection[name].wakeup();
    return true;
  }

}