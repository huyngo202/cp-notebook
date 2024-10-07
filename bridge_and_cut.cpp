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
int n, m;
vector<int> adj[mxN];
int num[mxN], low[mxN], dt = 0;
int cut, bridge;

void dfs(int u, int p = 0) {
    num[u] = ++dt;
    low[u] = n + 1;
    int iscut = 0, nchild = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!num[v]) {
            ++nchild;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[v])
                ++bridge;
            if ((nchild == 2 && p == 0) ||
                (num[u] <= low[v] && p != 0))
                iscut = 1;
        }
        else
            low[u] = min(low[u], num[v]);
    }
    cut += iscut;
}

int32_t main() {
    fastIO();
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    rep(i, 1, n)
        if (!num[i])
            dfs(i);
    cout << cut << " " << bridge;
    return 0;
}
