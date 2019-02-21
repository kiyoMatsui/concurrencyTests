#include <iostream>
#include <thread>
#include <chrono>
#include <deque>

struct data {
  int a = 0;
  char b[10000];
  double c = 1.0;
};

int vectorTraverse10k() {
  using namespace std::chrono_literals;
  std::deque<data*> container;
  data d;
  for (int n = 0; n < 10000; n++) {
    container.push_back(&d);
  }

  double e = 0.0;
  auto start = std::chrono::high_resolution_clock::now();
  for (auto& x : container) {
    x->c = e;
  } 
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "vectorTraverse10k runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

