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
#define sz(x) ((ll)(x).size())
#define ar array
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1e6 + 5;
int n;
vector<int> adj[mxN];
ll ans = 0, d[mxN];
int siz[mxN], dp[mxN];

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        dp[u] -= dp[v];
        dp[u] -= siz[v];
        siz[u] -= siz[v];
        siz[v] += siz[u];
        dp[v] += siz[u];
        dp[v] += dp[u];

        dfs(v, u);

        dp[v] -= dp[u];
        dp[v] -= siz[u];
        siz[v] -= siz[u];
        siz[u] += siz[v];
        dp[u] += siz[v];
        dp[u] += dp[v];
    }
}

int32_t main() {
    fast_cin();
    cin >> n;
    rep(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return 0;
}