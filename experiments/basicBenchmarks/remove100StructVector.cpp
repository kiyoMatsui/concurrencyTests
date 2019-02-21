#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

struct data {
  int a = 0;
  char b[10000];
  double c = 0.0;
};

int remove100StructVector() {
  using namespace std::chrono_literals;
  std::vector<data> container;
  data d;
  for(int n = 0; n < 100; n++) {
    container.push_back(d); //copies
  }
  auto start = std::chrono::high_resolution_clock::now();
  for(int n = 0; n < 100; n++) {
    container.pop_back(); 
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "remove100StructVector runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

