# Summary of Approach

I divided the work for the threads into eight equal sections, with each thread evaluating a contiguous range of integers. I used the Miller-Rabin algorithm to determine whether a number is prime. I also used a mutex lock to ensure that only one thread could modify the `primeCount`, `primeSum`, and `biggestPrimes` fields at a time. Finally, I used the C++ builtin `high_resolution_clock` to determine the execution time of my program.

# Correctness and Efficiency

Because I am using a mutex lock, there is no possibility of a race condition with regard to the `primeCount` and `primeSum` fields. I also verified that my output was correct using a brute force algorithm involving a prime sieve.

Miller Rabin is a highly efficient primality test that enables my code to finish running in around 5 seconds.

# Experimental Evaluation

Originally, I was using a less efficient primality test which ran in O(sqrt(n)) time. With this primality test, all of the threads finished executing in around 30 seconds. After replacing the less efficient primality test with Miller Rabin, my code was highly optimized.