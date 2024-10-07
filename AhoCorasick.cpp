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

const int mxN = 1e6 + 5;
int n, dp[5003], k;
string t, s[100001];

struct AhoCorasick {
    int c[mxN][26], d[mxN][26], sl[mxN], ol[mxN], m = 1, de[mxN];
    void ins(const string& s) {
        int u = 0;
        for (char a : s) {
            if (!c[u][a - 'a'])
                c[u][a - 'a'] = m++;
            u = c[u][a - 'a'];
        }
        ol[u] = u;
    }
    void work() {
        queue<int> qu;
        qu.push(0);
        while (qu.size()) {
            int u = qu.front();
            qu.pop();
            for (int i = 0; i < 26; ++i) {
                if (c[u][i]) {
                    int v = c[u][i];
                    de[v] = de[u] + 1;
                    sl[v] = d[sl[u]][i];
                    if (!ol[v])
                        ol[v] = ol[sl[v]];
                    d[u][i] = v;
                    qu.push(v);
                }
                else {
                    d[u][i] = d[sl[u]][i];
                }
            }

            dbg(u, de[u], sl[u], ol[u]);
            cerr << "d[u][i]:";
            rep(i, 0, 5)
                cerr << d[u][i] << " ";
            cerr << ln;
        }
    }
}T;

int32_t main() {
    fast_cin();
    // cin >> t >> k;
    // n = t.size();
    cin >> k;
    rep(i, 0, k - 1) {
        cin >> s[i];
        T.ins(s[i]);
    }
    T.work();

    // dp[0] = 1;
    // int u = 0;
    // rep(i, 1, n) {
    //     u = T.d[u][t[i - 1] - 'a'];
    //     int v = T.ol[u];
    //     while (v) {
    //         dp[i] = (dp[i] + dp[i - T.de[v]]) % M;
    //         v = T.ol[T.sl[v]];
    //     }
    // }
    // cout << dp[n];
    return 0;
    // }