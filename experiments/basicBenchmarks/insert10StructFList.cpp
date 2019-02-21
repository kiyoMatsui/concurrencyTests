#include <iostream>
#include <thread>
#include <chrono>
#include <forward_list>

struct data {
  int a = 0;
  char b[10000];
  double c = 0.0;
};

int insert10StructFList() {
  using namespace std::chrono_literals;
  std::forward_list<data> container;
  data d;
  auto start = std::chrono::high_resolution_clock::now();
  for (int n = 0; n < 10; n++) {
  container.push_front(d); //copies
  } 
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "insert10StructFList runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

