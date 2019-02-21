#include <iostream>
#include <thread>
#include <chrono>
#include <array>

int doNothing() {
  using namespace std::chrono_literals;
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "doNothing; this does nothing between clock now() calls. i.e. a empty benchmark. runtime "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()
            << " nanoseconds\n";
  return 0;
}

