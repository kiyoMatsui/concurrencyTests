#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

struct data {
  int a = 0;
  char b[10000];
  double c = 0.0;
};

int vectorSwapNPop1000() {
  using namespace std::chrono_literals;
  std::vector<data*> container;
  data d;
  for(int n = 0; n < 1002; n++) {
    container.push_back(&d); //copies
  }
  auto start = std::chrono::high_resolution_clock::now();
  for(auto iter=container.begin(); iter!=container.end();) {     
    if(container.size() > 2) {
      std::swap(*iter, container.back());
      container.pop_back();
    } else {
      //dothings
      iter++;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "vectorSwapNPop1000 runtime "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " microseconds\n";
  return 0;
}

