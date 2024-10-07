#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(int x) { cerr << x; } void __print(long int x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ll long long
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define siz(x) ((ll)(x).size())
#define ar array
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 2e5 + 5;
int n;
struct node {
    ll mx = 0, mn = INF, s = 0;
    node() {}
    node(ll a) :mx(a), mn(a), s(a) {}
    node(ll a, ll b, ll c) : mx(a), mn(b), s(c) { }
    node operator + (const node& other) const {
        return node(
            max(mx, other.mx),
            min(mn, other.mn),
            s + other.s
        );
    }
}t[2 * mxN];

void upd(int p, node value) {
    for (t[p += n] = value; p >>= 1;)
        t[p] = t[p << 1] + t[p << 1 | 1];
}

node query(int l, int r) {
    ++r;
    node res1, res2;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res1 = res1 + t[l++];
        if (r & 1) res2 = t[--r] + res2;
    }
    return res1 + res2;
}

// void upd(int l1, int x, int i = 1, int l2 = 1, int r2 = n) {
//     if (l2 == r2) {
//         st[i] = x;
//         return;
//     }
//     int m2 = (l2 + r2) / 2;
//     if (l1 <= m2)
//         upd(l1, x, i * 2, l2, m2);
//     else
//         upd(l1, x, i * 2 + 1, m2 + 1, r2);
//     st[i] = merge(st[i * 2], st[i * 2 + 1]);
// }


int32_t main() {
    fast_cin();
    int q, qt;
    ll u, v;
    cin >> n >> q;
    rep(i, 1, n) {
        cin >> u;
        upd(i, { u,u,u });
    }
    rep(i, 1, q) {
        cin >> qt >> u >> v;
        if (qt == 1)
            upd(u, { v,v,v });
        else
            cout << query(u, v).mn << ln;
    }
    return 0;
}