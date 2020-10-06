#include "test_lib.h"

// Test semafore access through libs
void reduce_semafore(std::string name){
  fulss::wait(name);
}