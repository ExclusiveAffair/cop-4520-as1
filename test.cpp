#include <bits/stdc++.h>
#include <thread>
using namespace std;
using ll = long long;

int main() {
    int ct = 0;
    ll sum = 0;
    vector<bool> prime(1e8, true);
    for (int i = 2; i < prime.size(); i++) {
        if (!prime[i]) continue;
        ct++;
        sum += i;
        for (int j = i+i; j < prime.size(); j += i) prime[j] = false;
    }
    cout << ct << " " << sum << endl;
}