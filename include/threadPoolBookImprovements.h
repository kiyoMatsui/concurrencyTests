#ifndef THREADPOOL_BOOK
#define THREADPOOL_BOOK

#include <vector>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "tsQueueBook.h"

class join_threads {
  std::vector<std::thread> &threads;

public:
  explicit join_threads(std::vector<std::thread> &threads_)
      : threads(threads_) {}
  ~join_threads() {
    for (unsigned long i = 0; i < threads.size(); ++i) {
      if (threads[i].joinable())
        threads[i].join();
    }
  }
};

class thread_pool {
  std::atomic_bool done;
  threadsafe_queue<std::function<void()>> work_queue;
  std::vector<std::thread> threads;
  mutable std::mutex m;
  std::condition_variable cv;
  join_threads joiner;

  void worker_thread() {
    while (!done.load()) {
      std::function<void()> task;
      if (work_queue.try_pop(task)) {
        task();
      } else {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [this]{return !(work_queue.empty()) || done.load(); });
        if (done.load()) {
          break;
        }
      }
    }
  }

public:
  thread_pool() : done(false), joiner(threads) {
    unsigned const thread_count = std::thread::hardware_concurrency();
    try {
      for (unsigned i = 0; i < thread_count; ++i) {
        threads.push_back(std::thread(&thread_pool::worker_thread, this));
      }
    } catch (...) {
      done.exchange(true);
      throw;
    }
  }

  ~thread_pool() {
    done.exchange(true);
    cv.notify_all();
    for (auto& n : threads) {
      n.join();
    }
  }

  template <typename FunctionType> void submit(FunctionType f) {
    work_queue.push(std::function<void()>(f));
    cv.notify_one();
  }
};

#endif
