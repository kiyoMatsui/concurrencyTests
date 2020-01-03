# concurrencyTests
Benchmarking, tests and some improvements of the concurrency patterns found in the C++ Concurrency in Action Book Original code found here: https://www.manning.com/CPlusPlusConcurrencyinAction (Boost Software License).
Other tests have been added over time...

# notes
Arithmetic with atomics is much slower than when using fundamental types; also, the thread safe containers are much slower as expected. Trivial tests do show that Callgrind can sometimes be wrong. Looks like spinning a thread vs using the basic thread pool is over 20 times slower.
