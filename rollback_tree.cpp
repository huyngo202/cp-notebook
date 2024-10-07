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
int n, q;
ll ans[mxN];
ar<int, 2> que[mxN];
struct edge {
    char qr;
    int val;
};
vector<pair<int, edge>> adj[mxN];

vector<int> v, pending_delete;
void add(int x) {
    v.push_back(x);
}

void del(int x) {
    pending_delete.push_back(x);
}

// count less thanx
ll query(int x) {
    vector<int> clone = v;
    v.clear();
    sort(all(clone));
    sort(all(pending_delete));
    for (int i = 0, j = 0; i < clone.size(); ++i) {
        if (j < pending_delete.size() && clone[i] == pending_delete[j])
            ++j;
        else
            v.push_back(clone[i]);
    }
    ll ret = 0;
    for (int i = 0; i < v.size(); ++i) {
        int j = lower_bound(all(v), x - v[i]) - v.begin();
        j = min(i - 1, j - 1);
        if (v[i] + v[j] < x)
            ret += j + 1;
    }
    return ret;
}

void dfs(int u) {
    dbg(u);
    for (auto [v, e] : adj[u]) {
        if (e.qr == '+') {
            add(e.val);
            dfs(v);
            del(e.val);
        }
        else if (e.qr == '-') {
            del(e.val);
            dfs(v);
            add(e.val);
        }
        else if (e.qr == '?')
            ans[e.val] = query(que[u][1] + 1) - query(que[u][0]);
    }
}

int32_t main() {
    fastIO();
    cin >> n >> q;
    rep(i, 1, n) {
        int x; cin >> x;
        add(x);
    }
    int curNode = 0, nNode = 0;
    rep(i, 1, q) {
        string qr; int x, y;
        cin >> qr >> x;
        if (qr == "add")
            adj[curNode].push_back({ ++nNode, {'+',x} });
        else if (qr == "del")
            adj[curNode].push_back({ ++nNode , {'-',x} });
        else if (qr == "ask") {
            cin >> y;
            adj[curNode].push_back({ -1, {'?',i} });
            que[curNode] = { x, y };
        }
        else
            curNode = x - 1;
        if (qr != "ask")
            ans[i] = -1;
    }
    dfs(0);
    rep(i, 1, q) if (ans[i] >= 0)
        cout << ans[i] << ln;
    return 0;
}