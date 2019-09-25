#include <iostream>
#include <thread>

#include "myExceptions.h"

int basicTests() {
  try {
    throw MyException();
  } catch (std::exception &e) {
    std::cerr << "MyException should be caught: " ;
    std::cerr << e.what() << std::endl;
  }
  
  try {
    throw MyExceptionExp(42);
  } catch (MyExceptionExp &e) {
    std::cerr << "MyExceptionExp should be caught  with code: "<< e.getCode() << ": ";
    std::cerr << e.what() << std::endl;
  }
  
  try {
    throw MyExceptionHierarchy();
  } catch (std::exception &e) {
    std::cerr << "MyExceptionHierarchy should be caught: ";
    std::cerr << e.what() << std::endl;
  }
  std::exception_ptr Globalex(nullptr); // do something better here
  // move between threads
  std::thread t1([&](){
      std::exception_ptr ex(nullptr);
      try {
        throw MyExceptionHierarchy();
        //throw MyExceptionExp(42); won't work due to interface change
      }
      catch (std::exception &e) {
        ex = std::current_exception();
        std::cerr << "Caught MyExceptionHierarchy and assign to ptr, check: " << e.what() << "\n";
        // maybe do something elase here like handle(ex)
      }
      Globalex = ex; // probably not this
    });
  t1.join();
  try {
    if (Globalex) { 
      std::rethrow_exception(Globalex);
    }
  }
  catch (std::exception &e) {
    std::cerr << "Caught MyExceptionHierarchy from thread, check: " << e.what() << "\n\n\n";
  }
  return 0;
}
