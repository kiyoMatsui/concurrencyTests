/*-------------------------------*\
Copyright 2019 Kiyo Matsui
KiyosGameEngine v0.73
Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/
\*-------------------------------*/

#include <iostream>
#include <thread>
#include <chrono>
#include <shared_mutex>

int doNothing();
int microSeconds10k();
int for100k();
int insert10PtrVector();
int insert10StructVector();
int insert10PtrFList();
int insert10StructFList();
int remove100PtrVector();
int remove100StructVector();
int remove100PtrFList();
int remove100StructFList();
int vectorTraverse10k();
int fListTraverse10k();
int dequeTraverse10k();
int vectorSwapNPop1000();
int spinThread();

int main() {
  doNothing();
  microSeconds10k();
  for100k();
  
  insert10PtrVector();
  insert10StructVector();
  insert10PtrFList();
  insert10StructFList();

  remove100PtrVector();
  remove100StructVector();
  remove100PtrFList();
  remove100StructFList();

  vectorTraverse10k();
  fListTraverse10k();
  dequeTraverse10k(); // can be faster in some strange cases.

  vectorSwapNPop1000();
  
  spinThread();
}

