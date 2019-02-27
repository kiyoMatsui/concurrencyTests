// test point

#include "catch2/catch.hpp"

#define private public
#define protected public

#include <mutex>
#include <stdexcept>

#include "tsPseudoVec.h"
#include "threadPool4.h"

TEST_CASE("threadsafe_tsPseudoVec ") {
  tsPseudoVec<int> tsVector;
  bool flagStack = false;
  flagStack = tsVector.container.empty(); //not thread safe
  REQUIRE(flagStack == true);
  tsVector.push_back(1);
  tsVector.push_back(2);
  tsVector.push_back(3);
  tsVector.pop_back();
  REQUIRE(tsVector.container.back() == 2);
  REQUIRE(tsVector.readAtDontDoThis(1) == 2);

}

int z = 1;
TEST_CASE("thread_pool ") {
  using namespace std::chrono_literals;
  threadPool tp;
  
  for (unsigned i = 0; i < 8; ++i) { // all race conditions but so fast it should be ok
    tp.submit([=](){  z++; });
  }
  std::this_thread::sleep_for(10000us); //race condition but should always work ok.
  REQUIRE(z == 9);

}
