#include <iostream>
#include <thread>
#include <chrono>
#include "threadPoolBook.h"

int useThreadPool() {
  using namespace std::chrono_literals;
  thread_pool tp;
  auto start = std::chrono::high_resolution_clock::now();
  tp.submit([=](){  std::this_thread::sleep_for(10000us); });
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "useThreadPool runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

