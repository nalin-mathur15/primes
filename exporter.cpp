#include <bits/stdc++.h>
#include "primes.cpp"
using namespace std;

static void write_csv_line(const string &path, const vector<int> &v) {
    ofstream out(path);
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) out << ',';
        out << v[i];
    }
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <n> <out_dir>\n";
        return 1;
    }
    long long N_in = atoll(argv[1]);
    if (N_in < 0) N_in = 0;
    if (N_in > INT_MAX) N_in = INT_MAX;
    int n = static_cast<int>(N_in);

    string outdir = argv[2];
    if (!outdir.empty() && outdir.back() == '/') outdir.pop_back();

    vector<int> p = primesTill(n);
    vector<int> q = qprimesTill(n);
    vector<int> dq = gaps(q);

    write_csv_line(outdir + "/p.csv",  p);
    write_csv_line(outdir + "/q.csv",  q);
    write_csv_line(outdir + "/dq.csv", dq);

    return 0;
}
