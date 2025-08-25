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
    vector<int> primesTill() const {
        vector<int> primes;
        if (n >= 2) primes.push_back(2);
        for (int i = 1; (2*i+1) <= n; ++i) {
            if (!isCompositeOdd[i]) primes.push_back(2*i + 1);
        }
        return primes;
    }  
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N_in;
    if (!(cin >> N_in)) return 0;
    if (N_in < 0) N_in = 0;
    if (N_in > INT_MAX) N_in = INT_MAX;
    int n = static_cast<int>(N_in);
    Sieve s(n);
    vector<int> p = s.primesTill();
    vector<int> q;
    for (long long k = 0; ; ++k) {
        long long val = k*k + 1;
        if (val > n) break;
        if (s.isPrime(static_cast<int>(val))) q.push_back(static_cast<int>(val));
    }
    vector<int> dq;
    vector<int> dp;
    if (q.size() >= 2) {
        dq.reserve(q.size() - 1);
        for (size_t i = 1; i < q.size(); ++i) {
            dq.push_back(q[i] - q[i-1]);
        }
    }
    if (p.size() >= 2) {
        dp.reserve(p.size() - 1);
        for (size_t i = 1; i < p.size(); ++i) {
            dp.push_back(p[i] - p[i-1]);
        }
    }
    auto print_vec = [](const vector<int>& v) {
        for (size_t i = 0; i < v.size(); ++i) {
            if (i) cout << " ";
            cout << v[i];
        }
        cout << '\n';
    };

    print_vec(p);
    print_vec(dp);
    print_vec(q);
    print_vec(dq);

    return 0;
}