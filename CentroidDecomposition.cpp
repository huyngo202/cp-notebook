#include <bits/stdc++.h>  
using namespace std;
using ll = long long;
using i64 = long long;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define ar array
int Bit(int mask, int b) { return (mask >> b) & 1; }
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 2e5 + 5;
int n, k;
vector<int> adj[mxN];
int s[mxN], cnt[mxN]{ 1 };
bitset<mxN> del;
ll ans = 0;

void _dfs(int u, int p = 0) {
    s[u] = 1;
    for (int v : adj[u]) if (!del[v] && v != p) {
        _dfs(v, u);
        s[u] += s[v];
    }
}

int getCentroid(int u, int p, int m) {
    for (int v : adj[u]) if (v != p && !del[v]) {
        if (s[v] * 2 > m)
            return getCentroid(v, u, m);
    }
    return u;
}

void getCnt(int u, int p, bool filling, int depth = 1) {
    if (filling) ++cnt[depth];
    else ans += cnt[k - depth];
    if (depth == k) return;
    for (int v : adj[u])
        if (v != p && !del[v])
            getCnt(v, u, filling, depth + 1);
}

void decomposition(int u = 1) {
    _dfs(u);
    int centroid = getCentroid(u, 0, s[u]);
    del[centroid] = true;

    for (int v : adj[centroid]) {
        if (!del[v])
            getCnt(v, centroid, false),
            getCnt(v, centroid, true);
    }
    for (int i = 1; i < n; ++i)
        if (cnt[i] != 0) cnt[i] = 0;
        else break;

    for (int v : adj[centroid])
        if (!del[v])
            decomposition(v);
}

int32_t main() {
    fast_cin();
    cin >> n >> k;
    rep(i, 2, n) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    decomposition();
    cout << ans;
    return 0;
}