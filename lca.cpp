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
int n;
vector<int> adj[mxN];
int dep[mxN], up[mxN][20];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= 19; ++i)
        up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v : adj[u]) if (v != p) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; --i)
        if (dep[up[u][i]] >= dep[v])
            u = up[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; --i)
        if (up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];
    return up[u][0];
}

int32_t main() {
    fastIO();
    int q;
    cin >> n >> q;
    rep(i, 2, n) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    ll u, v, u1, v1, u2, v2;
    cin >> u >> v >> u1 >> v1 >> u2 >> v2;
    int ans = lca(u - 1, v - 1) + 1;
    rep(i, 2, q) {
        u = (u * u1 + u2) % n + 1;
        v = (v * v1 + v2) % n + 1;
        ans ^= (lca(u - 1, v - 1) + 1);
    }
    cout << ans;
    return 0;
}
