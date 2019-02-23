

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>

struct data {
  std::atomic_bool flag1 = false;
  std::atomic_bool flag2 = false;  
  std::array<int, 5> a = {{1, 2, 3, 4, 5}};
  std::array<int, 5> a2 = {{1, 2, 3, 4, 5}};
  char b[1000000]; // large array so probably no longer on same cache line.
  std::array<int, 5> c = {{1, 2, 3, 4, 5}};
  std::array<int, 5> c2 = {{1, 2, 3, 4, 5}};
};

int threadA(data* aData) {
  using namespace std::chrono_literals;
  (aData->flag1).store(true); //rudamentary sync
    while (!aData->flag2) {
  } 
  for (int n = 0; n < 1000000000; n++) {
    for (auto& m : aData->c) {
      m++;
    }
    for (auto& m : aData->c2) {
      m++;
    }    
  } 
  return 0;
}



int main() {
  using namespace std::chrono_literals;
  data x;
  data* y = &x;
  auto start = std::chrono::high_resolution_clock::now();
  std::thread t1([=](){ threadA(y); });
  while (!x.flag1) { //rudamentary sync
  }
  (x.flag2).store(true);  
  for (int n = 0; n < 1000000000; n++) {
    for (auto& m : x.a) {
      m++;
    }
    for (auto& m : x.a2) {
      m++;
    }    
  } 
  t1.join();
  auto end = std::chrono::high_resolution_clock::now();  
  std::cout << "04NoFalseSharingTest runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}
