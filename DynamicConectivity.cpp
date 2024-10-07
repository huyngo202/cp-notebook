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

// Usage: int t = uf.time(); ...; uf.rollback(t);
struct RollbackUF {
    vector<int> e; vector<pair<int, int>> st; int comps = 0;
    RollbackUF(int n = 1) { init(n); }
    void init(int n) { e.assign(n + 1, -1);  comps = n; }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return st.size(); }
    void rollback(int t) {
        comps += (time() - t) / 2;
        for (int i = time(); i-- > t;)
            e[st[i].first] = st[i].second;
        st.resize(t);
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        st.emplace_back(a, e[a]); st.emplace_back(b, e[b]);
        e[a] += e[b]; e[b] = a;
        --comps;
        return true;
    }
};
const int mxN = 2e5 + 5;
int n, m, q;
vector<ar<int, 2>> st[mxN * 4];
RollbackUF uf;

void upd(int l1, int r1, ar<int, 2> e, int i = 1, int l2 = 0, int r2 = q) {
    if (l1 > r2 || l2 > r1) return;
    if (l1 <= l2 && r2 <= r1) {
        st[i].push_back(e);
        return;
    }
    int m2 = (l2 + r2) / 2;
    upd(l1, r1, e, i << 1, l2, m2);
    upd(l1, r1, e, i << 1 | 1, m2 + 1, r2);
}

int ans[mxN];
void solve(int i = 1, int l2 = 0, int r2 = q) {
    int t = uf.time();
    for (auto [u, v] : st[i])
        uf.join(u, v);
    if (l2 == r2) {
        ans[l2] = uf.comps;
    }
    else {
        int m2 = (l2 + r2) / 2;
        solve(i << 1, l2, m2);
        solve(i << 1 | 1, m2 + 1, r2);
    }
    uf.rollback(t);
}

int32_t main() {
    fastIO();
    cin >> n >> m >> q;
    uf.init(n);
    map<ar<int, 2>, int> mp;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        mp[{u, v}] = 0;
    }
    rep(i, 1, q) {
        int qr, u, v; cin >> qr >> u >> v;
        if (u > v) swap(u, v);
        if (qr == 1)
            mp[{u, v}] = i;
        else {
            upd(mp[{u, v}], i - 1, { u,v });
            mp.erase({ u,v });
        }
    }
    for (auto [e, t] : mp)
        upd(t, q, e);
    solve();
    rep(i, 0, q)
        cout << ans[i] << ' ';
    return 0;
}