#include "input.h"
#include <cstdio>
#include <cstring>

namespace fulio {
  /********************
   * InBuff functions
   * *****************/
  // Loop to capture all inputs and store them in inputStructure
  void InBuff::inputLoop(){
    while(active){
      char c;
      c = getchar();
      fulss::lock(SEM_NAME);
      switch ( c ){
        case 'w':
          input.setInput(0);
          break;
        case 's':
          input.setInput(1);
          break;
        case 'a':
          input.setInput(2);
          break;
        case 'd':
          input.setInput(3);
          break;
        case 'i':
          input.setInput(4);
          break;
        case 'p':
          input.setInput(5);
          break;
        case 'q':
          input.setInput(6);
          break;
        default:
          input.setInput(7);
          break;
      }
      input.setInput(7);
      fulss::unlock(SEM_NAME);
    }
  }

  // Creates a thread to get the inputs with locking game
  void InBuff::start(){
    fulss::create_mutex(SEM_NAME);
    active = true;
    t = std::thread(&InBuff::inputLoop, this);
  }

  // Stops input capturing
  void InBuff::stop(){
    active = false;
    t.join();
  }

  // Returns a copy of the inputStructure
  inputStructure InBuff::getInputs(){
    fulss::lock(SEM_NAME);
    inputStructure copy = input;
    input.reset();
    fulss::unlock(SEM_NAME);
    return copy;
  }

  /********************
  * inputStructure functions
  * *********************/
  void inputStructure::setInput(int index){
    inputs[index] = true;
  }
  void inputStructure::setInput(inTypes index){
    inputs[index] = true;
  }
  bool inputStructure::getInput(int index){
    return inputs[index];
  }
  bool inputStructure::getInput(inTypes index){
    return inputs[index];
  }
  void inputStructure::reset(){
    memset(inputs, false, 8);
  }
}
