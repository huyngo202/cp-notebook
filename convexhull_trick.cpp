#include <bits/stdc++.h>  
using namespace std;
#define ll long long
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define siz(x) ((ll)(x).size())
#define ar array
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 5e4 + 5;
int n, m;
struct line {
    ll m, k; line() {}
    line(ll a, ll b) : m(a), k(b) {}
    ll cal(ll x) { return m * x + k; }
};
vector<line> hull;

bool bad(line l1, line l2, line l3) {
    return (l3.k - l1.k) * (l1.m - l2.m) < (l2.k - l1.k) * (l1.m - l3.m);
}

void add(ll m, ll k) {
    line l = line(m, k);
    while (siz(hull) >= 2 && bad(hull.end()[-2], hull.end()[-1], l))
        hull.pop_back();
    hull.push_back(l);
}

int pt = 0;
ll query(ll x) {
    if (pt >= siz(hull))
        pt = siz(hull) - 1;
    while (pt < siz(hull) - 1 &&
        hull[pt + 1].cal(x) < hull[pt].cal(x))
        ++pt;
    return hull[pt].cal(x);
}

int32_t main() {
    fast_cin();
    cin >> m;
    vector<dt> a(m), rect;
    rep(i, 0, m - 1) cin >> a[i][0] >> a[i][1];
    sort(all(a));
    rep(i, 0, m - 1) {
        while (siz(rect) > 0 && rect.back()[1] <= a[i][1])
            rect.pop_back();
        rect.push_back(a[i]);
    }
    n = siz(rect);
    ll cost;
    add(rect[0][1], 0);
    rep(i, 0, n - 1) {
        cost = query(rect[i][0]);
        if (i < n - 1)
            add(rect[i + 1][1], cost);
    }
    cout << cost;
    return 0;
}
// 100
// 325
// 400
// 500
// 500