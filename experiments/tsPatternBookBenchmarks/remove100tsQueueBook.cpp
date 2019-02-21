#include <iostream>
#include <thread>
#include <chrono>
#include "tsQueueBook.h"

struct data {
  int a = 0;
  char b[10000];
  double c = 0.0;
};

int remove100tsQueueBook() {
  using namespace std::chrono_literals;
  threadsafe_queue<data*> container;
  data d;
  for(int n = 0; n < 100; n++) {
    container.push(&d); //copies
  }
  auto start = std::chrono::high_resolution_clock::now();
  for(int n = 0; n < 100; n++) {
    container.wait_and_pop(); 
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "remove100tsQueueBook runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

