# concurrencyTests
Benchmarking, tests and some improvements of the concurrency patterns found in the C++ Concurrency in Action Book Original code found here: https://www.manning.com/CPlusPlusConcurrencyinAction (Boost Software License).
Other tests have been added over time...

# notes
mass arithmetic with atomics is much slower than when using fundamental types; also, the thread safe containers are much slower as expected. The cache line ping pong and false sharing tests show around a 10% slowdown, this test was flawed and will be improved in future. All these trivial tests should be viewed with caution and compared with Callgrind. Trivial tests do show that Callgrind can sometimes be wrong. Looks like spinning a thread vs using the basic thread pool is over 20 times slower.
