#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;
using ll = long long;

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

int primeCount = 0;
ll primeSum = 0;
vector<int> biggestPrimes;
mutex m;

const int NUM_THREADS = 8, PRIMES = 1e8, BIGGEST_PRIMES = 10;

void countPrimes(int start, int end, bool record) {
    for (int num = end; num >= start; num--) {
        if (isPrime(num)) {
            m.lock();
            primeCount++;
            primeSum += num;
            if (record && biggestPrimes.size() < BIGGEST_PRIMES) {
                biggestPrimes.push_back(num);
            }
            m.unlock();
        }
    }
}

int main() {
    ofstream primes;
    primes.open("primes.txt");
    
    auto startTime = high_resolution_clock::now();

    vector<thread> threads;
    
    vector<int> ends;
    for (int i = 1; i <= NUM_THREADS; i++) {
        ends.push_back(PRIMES * i / NUM_THREADS);
    }

    int start = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread th(countPrimes, start, ends[i], i == NUM_THREADS - 1);
        threads.push_back(move(th));
        start = ends[i] + 1;
    }

    for (auto& th : threads) {
        th.join();
    }

    auto stopTime = high_resolution_clock::now();
    duration<double> elapsed_seconds = stopTime - startTime;

    primes << elapsed_seconds.count() << " " << primeCount << " " << primeSum << '\n';

    while (!biggestPrimes.empty()) {
        primes << biggestPrimes.back() << '\n';
        biggestPrimes.pop_back();
    }
    primes.close();
}