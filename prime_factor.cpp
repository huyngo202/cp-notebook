#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
#define ll long long
#define ln "\n"
#define dbg(x) cout<<#x<<" = "<<x<<ln
#define pb push_back
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define sz(x) ((ll)(x).size())
#define infile() if (fopen("in", "r")) freopen("in", "r", stdin);
#define ar array

const ll base = 311;
const ll MOD = 998244353, M = 1e9 + 7, INF = 2e18;
const int mxN = 1e6 + 5;
int n;

const int mxA = 1e7;
int lpf[mxA + 1];
vector<int> pfs;

int phi[mxN];
int md[mxN];

vector<ar<int, 2>> fact(int x) {
    vector<ar<int, 2>> a;
    while (x > 1) {
        int p = md[x];
        int cnt = 0;
        while (x % p == 0 && x > 1) {
            ++cnt;
            x /= p;
        }
        a.push_back({ p, cnt });
    }
    return a;
}

map<ll, int> fact(ll x) {
    map<ll, int> mp;
    for (ll i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x > 1 && x % i == 0) {
                ++cnt;
                x /= i;
            }
            mp[i] += cnt;
        }
    }
    if (x > 1) mp[x]++;
    return mp;
}

void init(int n = 1e6) {
    for (int i = 2; i <= n; ++i)
        if (md[i] == 0)
            for (int j = i; j <= n; j += i)
                md[j] = i;
}

void phi_euler() {
    phi[1] = 1;
    rep(i, 2, n) {
        if (md[i] == i)
            phi[i] = i - 1;
        else {
            int x = md[i], k = 1;
            while (i % (x * md[i]) == 0) {
                x *= md[i];
                ++k;
            }
            phi[i] = phi[i / x] * (x - x / md[i]);
        }
    }
}

vector<bool> prime;
void sieve(int n = 1e6) {
    prime.resize(n + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 1; i * i <= n; ++i)
        if (prime[i])
            for (int j = i * i; j <= n; j += i)
                prime[j] = false;
}

// for (int i = 2; i <= mxA; ++i) {
//     if (!lpf[i]) {
//         pfs.push_back(i);
//         lpf[i] = i;
//     }
//     for (int j = 0; j < (int)pfs.size() && pfs[j] <= lpf[i] && i * pfs[j] <= mxA; ++j)
//         lpf[i * pfs[j]] = pfs[j];
// }
// /*
//     2: 2
//     3: 3; l(2*3) = 2, l(3*3) = 3
//     4: ; l(2*4) = 2, l(3*4) = 3
//     5: 5; l(2*5) = 2, l(2*5) = 3, l(5*5) = 5
//     6: ; l(2*6) = 2, l(3*6) = 3, l(5*6) = 5
//     7: 7; l(2*7) = 2, l(3*7) = 3, l(5*7) = 5, l(7*7) = 7
//     */

// }

const int mX = 2e6;
int dv[mX + 1];
int32_t main() {
    fast_cin();
    memset(dv, 0, sizeof dv);
    rep(i, 1, mX)
        for (int j = i; j <= mX; j += i)
            dv[j]++;
    int mxx = *max_element(dv + 1, dv + mX + 1);
    cout << mxx << ln;
    rep(i, 1, mX)
        if (dv[i] == mxx)
            cout << i << ln;
    return 0;
}