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

const int mxN = 2e5 + 5;
int n, m;
int a[mxN], b[mxN];
vector<int> adj[mxN];
int c[mxN];
bool isBipart = true;

void dfs(int u, int cl) {
    c[u] = cl;
    for (int v : adj[u]) {
        if (c[v] >= 0 && c[v] != (cl ^ 1))
            isBipart = false;
        else if (c[v] < 0)
            dfs(v, cl ^ 1);
    }
}

int32_t main() {
    fast_cin();
    cin >> n >> m;
    rep(i, 1, m) cin >> a[i];
    rep(i, 1, m) cin >> b[i];
    rep(i, 1, m) {
        if (a[i] == b[i]) {
            cout << "No";
            return 0;
        }
        adj[a[i]].push_back(b[i]);
        adj[b[i]].push_back(a[i]);
    }
    memset(c, -1, sizeof c);
    rep(i, 1, n) if (c[i] == -1) dfs(i, 0);
    if (isBipart)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}