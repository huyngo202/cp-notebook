#include <bits/stdc++.h>  
using namespace std;
#define ll long long
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)

const ll MOD = 998244353, M = 1e9 + 7, INF = 1e18;
const int mxN = 1e6 + 5;
int n, m;
vector<int> adj[mxN];
int cnt = 0, num[mxN], low[mxN];
bitset<mxN> vis;
stack<int> st;

void dfs(int u) {
    low[u] = num[u] = ++cnt;
    st.push(u);
    for (int v : adj[u]) {
        if (!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], num[v]);
    }

    if (num[u] == low[u]) {
        cout << "new component:\n";
        while (st.size()) {
            int v = st.top();
            cout << v << " ";
            st.pop();
            if (v == u) break;
        }
        cout << '\n';
    }
}

int32_t main() {
    fast_cin();
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        // adj[v].push_back(u);
    }
    rep(i, 1, n)
        if (!num[i])
            dfs(i);
    return 0;
}