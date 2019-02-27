#ifndef THREADSAFEPSEUDOVEC
#define THREADSAFEPSEUDOVEC

#include <shared_mutex>
#include <memory>
#include <vector>

template <typename T>
class tsPseudoVec {
 public:
  tsPseudoVec() {}
  tsPseudoVec(const tsPseudoVec &arg) {
    std::lock_guard<std::shared_mutex> lock(arg.sm);
    container = arg.container;
  }
  tsPseudoVec &operator=(const tsPseudoVec &) = delete;

  void push_back(T new_value) {
    std::unique_lock<std::shared_mutex> lock(sm);
    container.push_back(std::move(new_value));
  }
  
  bool pop_back() {
    std::unique_lock<std::shared_mutex> lock(sm);
    if (container.empty()) {
      return false;
    }
    container.pop_back();
    return true;
  }

  //don't do this
  T& readAtDontDoThis(unsigned int pos) {
    std::shared_lock<std::shared_mutex> lock(sm);
    return container.at(pos);
  }

  std::vector<T> container;
  mutable std::shared_mutex sm;
};

#endif
