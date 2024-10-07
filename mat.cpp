#include <bits/stdc++.h>  
using namespace std;
using ll = long long;

int n, k;

const ll M = 1e9 + 7;
#define mat vector<vector<ll>> 
mat cn(int m, int n) {
    return mat(m, vector<ll>(n));
}
mat operator*(mat& a, mat& b) {
    mat c = cn(a.size(), b[0].size());
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b[0].size(); ++j)
            for (int l = 0; l < (int)a[0].size(); ++l) {
                c[i][j] += a[i][l] * b[l][j] % M;
                if (c[i][j] >= M) c[i][j] -= M;
            }
    return c;
}
mat operator^(mat& a, ll n) {
    mat r = cn(a.size(), a.size());
    for (int i = 0; i < (int)a.size(); ++i)
        r[i][i] = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1)
            r = r * a;
        a = a * a;
    }
    return r;
}

int32_t main() {
    return 0;
}
