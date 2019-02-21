#include <iostream>
#include <thread>
#include <chrono>
#include "tsListBook.h"

struct data {
  int a = 0;
  char b[10000];
  double c = 0.0;
};

int insert10tsListBook() {
  using namespace std::chrono_literals;
  threadsafe_list<data*> container;
  data d;
  auto start = std::chrono::high_resolution_clock::now();
  for(int n = 0; n < 10; n++) {
    container.push_front(&d);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "insert10tsListBook runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

