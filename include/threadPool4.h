#ifndef THREADPOOL4
#define THREADPOOL4

#include <vector>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <queue>

template <unsigned int N = 4>
class threadPool {
 public:
  threadPool() {
    for (unsigned i = 0; i < N; ++i) {
      threads.emplace_back([=]() {
          for(;;) {
            m.lock();
            if (jobQueue.empty()) {
              m.unlock();
              if (killFlag) break;
              std::this_thread::yield();
            } else {
              std::function<void()> job = jobQueue.front();
              jobQueue.pop();
              m.unlock();
              job();
            }
          }
        });
      }
    }

  ~threadPool() {
    killFlag.exchange(true);
    for (auto& n : threads) {
      n.join();
    }
  }

  template <typename FunctionType>
  void submit(FunctionType functor) {
    std::lock_guard<std::mutex> lock(m);
    jobQueue.push(std::function<void()>(functor));
  }

 private:
  std::queue<std::function<void()>> jobQueue;
  std::vector<std::thread> threads;
  mutable std::mutex m;
  std::atomic_bool killFlag = false;
};

#endif
