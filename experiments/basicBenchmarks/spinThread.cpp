#include <iostream>
#include <thread>
#include <chrono>
#include <array>

int spinThread() {
  using namespace std::chrono_literals;
  auto start = std::chrono::high_resolution_clock::now();
  std::thread t1([](){ std::this_thread::sleep_for(10000us); });
  auto end = std::chrono::high_resolution_clock::now();
  t1.join();
  std::cout << "spinThread runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

