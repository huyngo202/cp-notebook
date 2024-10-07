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
#define siz(x) ((ll)(x).size())
#define ar array
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1e6 + 5;
int n;
ll h[mxN], c[mxN];

ll cost(int x) { ll s = 0; rep(i, 1, n) s += abs(h[i] - x) * c[i]; return s; }

void solve() {
    cin >> n;
    rep(i, 1, n) cin >> h[i];
    rep(i, 1, n) cin >> c[i];
    int A = 0, B = 1e4;
    // ON double

    // minimize
    // for (int i = 0; i < LOG; i++) {
    //     double m1 = (A * 2 + B) / 3.0;
    //     double m2 = (A + 2 * B) / 3.0;
    //     if (f(m1) > f(m2))
    //         A = m1;
    //     else
    //         B = m2;
    // }
    // ans = f(A);

    // ON INTEGER
    // int A = 0, B = 1e6;
    while (B - A > 4) {
        int m1 = (A + B) / 2;
        int m2 = (A + B) / 2 + 1;
        if (cost(m1) > cost(m2))
            A = m1;
        else
            B = m2;
    }

    ll ans = INF;
    for (int i = A; i <= B; i++)
        ans = min(ans, cost(i));
    cout << ans << ln;
}

int32_t main() {
    fast_cin();
    int t; cin >> t; for (int it = 1; it <= t; it++) { solve(); }
    return 0;
}