#include <bits/stdc++.h>
using namespace std;


struct Sieve {
    int n;
    vector<uint8_t> isCompositeOdd;
    explicit Sieve(int N) : n(N), isCompositeOdd(((N >= 1) ? ((N-1)/2 + 1) : 0), 0) {
        if (n < 3) return;
        int lim = static_cast<int>(sqrtl(n));
        for (int p = 3; p <= lim; p += 2) {
            if (!isComposite(p)) {
                long long start = 1LL * p * p;
                for (long long m = start; m <= n; m += 2LL * p) {
                    isCompositeOdd[(m-1) >> 1] = 1;
                }
            }
        }
    }

    inline bool isComposite(int m) const {
        if (m==2) return false;
        if (m < 2 || (m&1) == 0) return m!= 2;
        return isCompositeOdd[(m-1) >> 1];
    }
    inline bool isPrime(int m) const {
        if (m == 2) return true;
        if (m < 2 || (m & 1) == 0) return false;
        return !isCompositeOdd[(m - 1) >> 1];
    }
};

inline vector<int> primesTill(int n) {
    Sieve s(n);
    vector<int> primes;
    if (n >= 2) primes.push_back(2);
    for (int i = 1; (2*i+1) <= n; ++i) {
        if (!s.isCompositeOdd[i]) primes.push_back(2*i + 1);
    }
    return primes;
}  

inline vector<int> qprimesTill(int n) {
    Sieve s(n);
    vector<int> q;
    q.push_back(2);
    for (long long k = 2; ; k += 2) {
        long long val = k*k + 1;
        if (val > n) break;
        if (s.isPrime(static_cast<int>(val))) q.push_back(static_cast<int>(val));
    }
    return q;
}

inline vector<int> gaps(const vector<int>& v) {
    vector<int> g;
    if (v.size() >= 2) {
        g.reserve(v.size() - 1);
        for (size_t i = 1; i < v.size(); ++i) g.push_back(v[i] - v[i-1]);
    }
    return g;
}

