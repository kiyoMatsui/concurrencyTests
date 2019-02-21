#include <iostream>
#include <thread>
#include <chrono>
#include <forward_list>

struct data {
  int a = 0;
  char b[10000];
  double c = 1.0;
};

int fListTraverse10k() {
  using namespace std::chrono_literals;
  std::forward_list<data*> container;
  data d;
  for (int n = 0; n < 10000; n++) {
    container.push_front(&d);
  }

  double e = 0.0;
  auto start = std::chrono::high_resolution_clock::now();
  for (auto& x : container) {
    x->c = e;
  } 
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "fListTraverse10k runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

