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

const int mxN = 2e6 + 5;
int n;
string a, b;
int z[mxN];

int32_t main() {
    fast_cin();
    cin >> a >> b;
    a = b + a;
    int m = siz(b);
    n = siz(a);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && a[r] == a[r - i]) ++r;
            z[i] = r - l; --r;
        }
        else {
            int k = i - l;
            if (i + z[k] - 1 < r) z[i] = z[k];
            else {
                l = i;
                while (r < n && a[r] == a[r - i]) ++r;
                z[i] = r - l; --r;
            }
        }
    }
    rep(i, m, n - m)
        if (z[i] >= m)
            cout << i - m + 1 << " ";
    return 0;
}