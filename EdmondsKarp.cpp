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

const int mxN = 1e3 + 5;
int n, m, s, t;
vector<int> adj[mxN];
int c[mxN][mxN], f[mxN][mxN], trace[mxN], maxflow;

int bfs() {
    fill(trace, trace + n + 1, 0);
    trace[s] = -1;
    queue<int> qu;
    qu.push(s);
    while (qu.size()) {
        int u = qu.front();
        qu.pop();
        for (int v : adj[u]) {
            if (trace[v]) continue;
            if (f[u][v] == c[u][v]) continue;
            trace[v] = u;
            qu.push(v);
        }
    }
    return trace[t];
}

void incFlow() {
    int delta = INT_MAX;
    int v = t;
    while (v != s) {
        int u = trace[v];
        delta = min(delta, c[u][v] - f[u][v]);
        v = u;
    }
    maxflow += delta;
    v = t;
    while (v != s) {
        int u = trace[v];
        f[u][v] += delta;
        f[v][u] -= delta;
        v = u;
    }
}

int32_t main() {
    fastIO();
    cin >> n >> m >> s >> t;
    for (int u, v, i = 1; i <= m; ++i) {
        cin >> u >> v >> c[u][v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    maxflow = 0;
    while (bfs())
        incFlow();
    cout << maxflow;
    return 0;
}