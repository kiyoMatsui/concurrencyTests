

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>

struct data {
  std::atomic_bool flag1 = false;
  std::atomic_bool flag2 = false;  
  std::array<std::atomic_int, 5> a = {{1, 2, 3, 4, 5}};
  //char b[1000000]; // large array so probably no longer on same cache line.
  //char b[1]; // i.e. all data on same cache line
  //std::array<int, 5> c = {{1, 2, 3, 4, 5}};
};

int threadA(data* aData) {
  using namespace std::chrono_literals;
  (aData->flag1).store(true); //rudamentary sync
    while (!aData->flag2) {
  } 
  for (int n = 0; n < 10000000; n++) {
    for (auto& m : aData->a) {
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
  for (int n = 0; n < 10000000; n++) {
    for (auto& m : x.a) {
      m++;
    }
  } 
  t1.join();
  auto end = std::chrono::high_resolution_clock::now();  
  std::cout << "03FalseSharingTest runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}
