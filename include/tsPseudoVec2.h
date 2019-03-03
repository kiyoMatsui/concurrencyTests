#ifndef THREADSAFEPSEUDOVEC2
#define THREADSAFEPSEUDOVEC2

#include <mutex>
#include <memory>
#include <vector>

template <typename T>
class tsPseudoVec2 {
 public:
  tsPseudoVec2() {}
  tsPseudoVec2(const tsPseudoVec2 &arg) {
    std::lock_guard<std::shared_mutex> lock(arg.sm);
    container = arg.container;
  }
  tsPseudoVec2 &operator=(const tsPseudoVec2 &) = delete;

  void push_back(T new_value) {
    std::unique_lock<std::shared_mutex> lock(sm, std::try_to_lock);
    if(sm.owns_lock()) {
      container.push_back(std::move(new_value));
    } else {
      std::lock_guard<std::mutex> lock(m);
      tempContainer.push_back(std::move(new_value));
  }
  }
  
  bool pop_back() {
    std::unique_lock<std::shared_mutex> lock(sm, std::try_to_lock);
    if(sm.owns_lock()) {
      if (container.empty()) {
        return false;
      }
      container.pop_back();
      return true;
    } else {
      std::lock_guard<std::mutex> lock(m);
      if (tempContainer.empty()) {
        return false;
      }
      tempContainer.pop_back();
      return true;      
    }
  }

  bool pushTempItems() {
    std::lock_guard<std::shared_mutex> lock(am);
    std::lock_guard<std::mutex> lock(m);
    container.insert(std::end(container), std::begin(tempContainer), std::end(tempContainer));
  }

  std::vector<T> tempContainer;
  std::vector<T> container;
  mutable std::shared_mutex sm;
  mutable std::mutex m;
};

#endif
