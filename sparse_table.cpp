#include <bits/stdc++.h>  
using namespace std;

int n = 100000;

int32_t main() {
    vector<int> a(n);

    struct Info {
        int64_t min = 1e18;
        int64_t max = -1e18;
        Info operator + (const Info& p) {
            return Info{ std::min(min, p.min), std::max(max, p.max) };
        }
    };
    vector<vector<Info>> g(n, vector<Info>(21));

    for (int i = 0; i < n; ++i)
        g[i][0] = { a[i], a[i] };

    for (int j = 1; j < 21; ++j)
        for (int i = 0; i + (1 << j) <= n; ++i)
            g[i][j] = g[i][j - 1] + g[i + (1 << (j - 1))][j - 1];

    auto get = [&](int l, int r) -> Info {
        int k = log2(r - l + 1);
        return g[l][k] + g[r - (1 << k) + 1][k];
        };


}
