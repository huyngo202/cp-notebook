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
int a[mxN];

void compress() {
    vector<int> val;
    rep(i, 1, n)
        val.push_back(a[i]);
    sort(all(val));
    val.erase(unique(all(val)), val.end());
    rep(i, 1, n) a[i] = lower_bound(all(val), a[i]) - val.begin();
}

struct FenwickTree {
    ll f[mxN];
    void upd(int i, ll x) {
        for (; i < mxN; i += -i & i)
            f[i] += x;
    }
    ll get(int i) {
        ll r = 0;
        for (; i > 0; i -= -i & i) r += f[i];
        return r;
    }
    ll get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

void solve() {

}

int32_t main() {
    fast_cin();
    ll t; cin >> t;
    for (int it = 1; it <= t; it++) {
        solve();
    }
    return 0;
}