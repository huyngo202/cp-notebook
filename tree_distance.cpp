//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define siz(x) ((ll)(x).size())
#define ar array
using ll = long long;
int Bit(int mask, int b) { return (mask >> b) & 1; }
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1e6 + 5;
int n;
int d[mxN], ans[mxN];
vector<int> adj[mxN];

void _dfs(int u = 1, int p = 0) {
    for (int v : adj[u]) {
        if (v == p) continue;
        _dfs(v, u);
        // diameter = max(diameter, d[u] + d[v] + 1);
        d[u] = max(d[u], d[v] + 1);
    }
}

void dfs2(int u = 1, int p = 0, int pd = 0) {
    ans[u] = max(d[u], pd);
    vector<ar<int, 2>> w{ {pd, 0} };
    for (int v : adj[u]) {
        if (v == p) continue;
        w.push_back({ d[v] + 1, v });
    }
    //    w.push_back({0, -1});
    sort(w.begin(), w.end(), greater<>());
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs2(v, u, w[0][1] == v ? w[1][0] + 1 : w[0][0] + 1);
    }
}

int32_t main() {
    fast_cin();
    // int t; cin >> t; for (int it = 1; it <= t; it++) { solve(); }
    cin >> n;
    rep(i, 2, n) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    _dfs();
    dfs2();
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";
    return 0;
}