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

const ll base = 311;
const ll MOD = 998244353, M = 1e9 + 7, INF = 1e18;
const int mxN = 1e6 + 5;
const int block_size = 512;
int n;

int cnt[mxN / block_size][mxN];
int a[mxN];

int qry(int l, int r, int k) {
    int bl = (l + block_size - 1) / block_size;
    int br = r / block_size;
    int res = 0;
    if (bl >= br) {
        rep(i, l, r)
            res += (a[i] == k);
        return res;
    }
    rep(i, l, bl * block_size - 1) res += (a[i] == k);
    rep(i, bl, br - 1) res += cnt[i][k];
    rep(i, br * block_size, r) res += (a[i] == k);
    return res;
}

int32_t main() {
    fast_cin();
    return 0;
}