


#include <iostream>
#include <thread>
#include <chrono>
#include "threadPoolBook.h"

struct dataFalseShareRisk {
  double a = 0.0;
  char b[1];
  double c = 0.0;
};

struct data {
  double a = 0.0;
  char b[1000000];
  double c = 0.0;
};

int threadA(data* a) {
  std::vector<double> container;
  for (int n = 0; n < 1000000; n++) {
    container.push_back(42.0);
  }
  for (auto x : container) {
    a->c = a->c * x;
  } 
  return 0;
}

int threadB(data* a) {
  std::vector<double> container;
  for (int n = 0; n < 1000000; n++) {
    container.push_back(42.0);
  }
  for (auto x : container) {
    a->c = a->c * x;
  } 
  return 0;
}

int main() {
  using namespace std::chrono_literals;
  thread_pool tp;
  data x;
  data* y = &x;
  auto start = std::chrono::high_resolution_clock::now();
  tp.submit( [=]() { threadA(y); });
  tp.submit( [=]() { threadB(y); });
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "03FalseSharingTest runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

