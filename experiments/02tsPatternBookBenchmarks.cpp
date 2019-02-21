


#include <iostream>
#include <thread>
#include <chrono>
#include <shared_mutex>

int insert10tsListBook();
int insert10tsQueueBook();
int insert10tsStackBook();
int remove100tsQueueBook();
int remove100tsStackBook();
int tsListBookTraverse10k();
int useThreadPool();

int main() {
  insert10tsListBook();
  insert10tsQueueBook();
  insert10tsStackBook();
  remove100tsQueueBook();
  remove100tsStackBook();

  tsListBookTraverse10k();
 
  useThreadPool();
}

