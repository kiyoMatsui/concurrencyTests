// test point

#include "catch2/catch.hpp"

#define private public
#define protected public

#include <mutex>
#include <stdexcept>

#include "tsStackBook.h"
#include "tsListBook.h"
#include "tsQueueBook.h"
#include "heirarchicalMutexBook.h"
#include "threadPoolBook.h"

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int do_low_level_stuff() { return 42; }

int low_level_func() {
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
  return do_low_level_stuff();
}

void high_level_stuff(int some_param) {}

void high_level_func() {
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
  high_level_stuff(low_level_func());
}

void thread_a() { high_level_func(); }

hierarchical_mutex other_mutex(100);
void do_other_stuff() {}

void other_stuff() {
  high_level_func();
  do_other_stuff();
}

void thread_b() {
  std::lock_guard<hierarchical_mutex> lk(other_mutex);
  other_stuff();
}

thread_local unsigned long
    hierarchical_mutex::this_thread_hierarchy_value(1000000);

TEST_CASE("hierarchical_mutex tests") {
  hierarchical_mutex m1(42);
  hierarchical_mutex m2(2000);
  m1.lock();
  m1.unlock();

  m2.try_lock();
  m2.unlock();
  
  thread_a();
  //thread_b(); // successfully outputs error
}

TEST_CASE("threadsafe_stack ") {
  threadsafe_stack<int> stack;
  bool flagStack = false;
  flagStack = stack.empty();
  REQUIRE(flagStack == true);
  stack.push(1);
  stack.push(2);
  stack.push(3);
  int a = 4;
  stack.pop(a);
  REQUIRE(a == 3);
  std::shared_ptr<int> b = std::make_shared<int>(5);
  b = stack.pop();
  REQUIRE(*b == 2);
}

TEST_CASE("threadsafe_list ") {
  threadsafe_list<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  std::shared_ptr<int> c = std::make_shared<int>(5);
  list.remove_if([=](int d){ if(d==4) return true; return false;});
  c = list.find_first_if([=](int d){ if(d==2) return true; return false;});
  REQUIRE(*c == 2);
  list.push_front(6);
  list.push_front(7);
  list.push_front(8);
  list.for_each([=](int d){ if(d==7) d++ ;}); //use int& to get reference otherwise it is a copy
  list.for_each([=](int d){ if(d!=5) REQUIRE(d != 5); });
}

TEST_CASE("threadsafe_queue ") {
  threadsafe_queue<int> queue; 
  bool flag = false;
  flag = queue.empty();
  REQUIRE(flag == true);
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(4);
  queue.push(5);
  int e = 6;
  flag = queue.try_pop(e);
  REQUIRE(e == 1);
  std::shared_ptr<int> f = std::make_shared<int>(7);
  f = queue.try_pop();
  REQUIRE(*f == 2);
  f = queue.wait_and_pop();
  REQUIRE(*f == 3);
  queue.wait_and_pop(e);
  REQUIRE(e == 4);
}

int z = 1;
TEST_CASE("thread_pool ") {
  using namespace std::chrono_literals;
  thread_pool tp;
  tp.submit([=](){  z++; });
  std::this_thread::sleep_for(10000us); //race condition but should always work ok.
  REQUIRE(z == 2);
}
