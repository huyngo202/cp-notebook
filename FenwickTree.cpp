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


template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n_ = 0) { init(n_); }
    void init(int n_) { n = n_ + 1; a.assign(n, T{}); }
    // x in [0, n]
    void add(int x, const T& v) {
        for (int i = x + 1; i <= n; i += -i & i)
            a[i - 1] = a[i - 1] + v;
    }
    // sum of [0, x)
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= -i & i)
            ans = ans + a[i - 1];
        return ans;
    }
    // sum of [l, r)
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int select(const T& k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};


signed main() {
    fastIO();
    /*
    Fenwick<int> fen(n);
    */
    int n = 10;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    dbg(a);
    Fenwick<int> fen(n);
    for (int i = 0; i < n; ++i)
        fen.add(i, a[i]);
    dbg(fen.sum(1));
    // for (int i = 0; i < n; ++i)
    //     cout << fen.sum(i) << " ";
    return 0;
}