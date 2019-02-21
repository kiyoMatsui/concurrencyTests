#include <iostream>
#include <thread>
#include <chrono>
#include "tsListBook.h"

struct data {
  int a = 0;
  char b[10000];
  double c = 1.0;
};

int tsListBookTraverse10k() {
  using namespace std::chrono_literals;
  threadsafe_list<data> container;
  data d;
  for (int n = 0; n < 10000; n++) {
    container.push_front(d);
  }

  double e = 0.0;
  auto start = std::chrono::high_resolution_clock::now();
  container.for_each([=](data& x){ x.c = e; }); // must be reference otherwise its a copy
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "tsListBookTraverse10k runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

