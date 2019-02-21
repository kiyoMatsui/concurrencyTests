

#include <iostream>
#include <thread>
#include <chrono>

int microSeconds10k() {
  using namespace std::chrono_literals;
  auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(10000us);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "microSeconds10k runtime "
      << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
      << " microseconds\n";
  return 0;
}

