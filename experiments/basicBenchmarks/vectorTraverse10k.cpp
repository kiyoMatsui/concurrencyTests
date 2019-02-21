#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

struct data {
  int a = 0;
  char b[10000];
  double c = 1.0;
};

int dequeTraverse10k() {
  using namespace std::chrono_literals;
  std::vector<data*> container;
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
  std::cout << "dequeTraverse10k runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

