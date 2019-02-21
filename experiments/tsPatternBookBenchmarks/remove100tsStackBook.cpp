#include <iostream>
#include <thread>
#include <chrono>
#include "tsStackBook.h"

struct data {
  int a = 0;
  char b[10000];
  double c = 0.0;
};

int remove100tsStackBook() {
  using namespace std::chrono_literals;
  threadsafe_stack<data*> container;
  data d;
  for(int n = 0; n < 100; n++) {
    container.push(&d); //copies
  }
  auto start = std::chrono::high_resolution_clock::now();
  for(int n = 0; n < 100; n++) {
    container.pop(); 
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "remove100tsStackBook runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

