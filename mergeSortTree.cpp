#include <bits/stdc++.h>  
using namespace std;
using ll = long long;
using i64 = long long;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ln "\n"
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define ar array
int Bit(int mask, int b) { return (mask >> b) & 1; }
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1e6 + 5;
int n;
int a[mxN];

struct node {
    vector<int> v;
}st[mxN * 4];

void build(int i = 1, int l = 1, int r = n) {
    if (l == r) {
        st[i].v = { a[l] };
        return;
    }
    int m = (l + r) / 2;
    build(i << 1, l, m);
    build(i << 1 | 1, m + 1, r);
    st[i].v.resize(r - l + 1);
    std::merge(all(st[i << 1].v), all(st[i << 1 | 1].v), st[i].v.begin());
}

int get(int l1, int r1, int k, int i = 1, int l2 = 1, int r2 = n) {
    if (l1 > r2 || l2 > r1) return 0;
    if (l1 <= l2 && r2 <= r1)
        return r2 - l2 + 1 - (upper_bound(all(st[i].v), k) - st[i].v.begin());
    int m2 = (l2 + r2) / 2;
    return get(l1, r1, k, i << 1, l2, m2) + get(l1, r1, k, i << 1 | 1, m2 + 1, r2);
}

int32_t main() {
    fastIO();
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    build();
    int q; cin >> q;
    rep(i, 1, q) {
        int l, r, x; cin >> l >> r >> x;
        cout << get(l, r, x) << ln;
    }
    return 0;
}