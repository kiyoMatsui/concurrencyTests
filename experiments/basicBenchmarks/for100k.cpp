#include <iostream>
#include <thread>
#include <chrono>
#include <array>

int for100k() {
  using namespace std::chrono_literals;
  auto start = std::chrono::high_resolution_clock::now();
  auto temp = std::chrono::high_resolution_clock::now();
  for (int n = 0; n < 100000; n++) {
    temp = std::chrono::high_resolution_clock::now();
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "for100k runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

