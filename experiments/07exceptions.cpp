#include <iostream>
#include <thread>
#include <chrono>

int basicTests();
int nestedExceptions();
int tryFunctionBlockConstructor();

int main() {
  std::cout << "Exception tests" << std::endl;
  basicTests();
  nestedExceptions();
  tryFunctionBlockConstructor();
}

