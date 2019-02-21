#include <iostream>
#include <thread>
#include <chrono>
#include <forward_list>

struct data {
  int a = 0;
  char b[10000];
  double c = 0.0;
};

int remove100StructFList() {
  using namespace std::chrono_literals;
  std::forward_list<data> container;
  data d;
  for(int n = 0; n < 100; n++) {
    container.push_front(d); //copies
  }
  auto start = std::chrono::high_resolution_clock::now();
  for(int n = 0; n < 100; n++) {
    container.pop_front(); 
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "remove100StructFList runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

