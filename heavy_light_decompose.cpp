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

const int mxN = 2e5 + 5;
int n, q;
int a[mxN], st[4 * mxN], dep[mxN], p[mxN], tp[mxN], sz[mxN], id[mxN], v[mxN];
int dt = 0;
vector<int> adj[mxN];

void upd(int idx, int val) {
    st[idx += n] = val;
    for (idx /= 2; idx; idx /= 2) st[idx] = max(st[2 * idx], st[2 * idx + 1]);
}

int qry(int lo, int hi) {
    int ra = 0, rb = 0;
    for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
        if (lo & 1) ra = max(ra, st[lo++]);
        if (hi & 1) rb = max(rb, st[--hi]);
    }
    return max(ra, rb);
}

int dfs_sz(int u, int par) {
    sz[u] = 1;
    p[u] = par;
    for (int v : adj[u]) {
        if (v == par)continue;
        dep[v] = dep[u] + 1;
        sz[u] += dfs_sz(v, u);
    }
    return sz[u];
}

void hld(int u, int p, int top) {
    id[u] = ++dt;
    tp[u] = top;
    upd(id[u], v[u]);
    int hv_ch = -1, hv_sz = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (sz[v] > hv_sz) {
            hv_sz = sz[v];
            hv_ch = v;
        }
    }
    if (hv_ch == -1) return;
    hld(hv_ch, u, top);
    for (int v : adj[u]) {
        if (v == p || v == hv_ch) continue;
        hld(v, u, v);
    }
}

int path(int u, int v) {
    int res = 0;
    while (tp[u] != tp[v]) {
        if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
        res = max(res, qry(id[tp[u]], id[u]));
        u = p[tp[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res = max(res, qry(id[u], id[v]));
    return res;
}

int lca(int u, int v) {
    while (tp[u] != tp[v]) {
        if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
        u = p[tp[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}

int32_t main() {
    fastIO();
    cin >> n >> q;
    rep(i, 1, n) cin >> v[i];
    rep(i, 2, n) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_sz(1, 1);
    hld(1, 1, 1);
    rep(i, 1, q) {
        int qt, u, v; cin >> qt >> u >> v;
        if (qt == 1)
            upd(id[u], v);
        else
            cout << path(u, v) << " ";
    }
    return 0;
}