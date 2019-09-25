#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "myExceptions.h"

void useLowerLevel() {
  try {
    std::ifstream file("thisFIleShouldNotExist.asdasdasd");
    file.exceptions(std::ios_base::failbit);
  } catch (std::exception &e) {
    std::throw_with_nested(MyException());
  }
}

void useInterface() {
  try {
    useLowerLevel();
  } catch (std::exception &e) {
    std::throw_with_nested(std::runtime_error("Low level function failed"));
  }
}

// from cpp reference
// prints the explanatory string of an exception. If the exception is nested,
// recurses to print the explanatory of the exception it holds
void print_exception(const std::exception& e, int level =  0)
{
    std::cerr << std::string(level, ' ') << "exception: " << e.what() << '\n';
    try {
        std::rethrow_if_nested(e);
    } catch(const std::exception& e) {
        print_exception(e, level+1);
    } catch(...) {}
}

int nestedExceptions() {
  try {
    useInterface();
  } catch (std::exception &e) {
    std::cerr << "Caught highest level exception\n" << e.what() << "\n";
    print_exception(e);
  }
  std:: cout << "\n\n";
  return 0;
}
