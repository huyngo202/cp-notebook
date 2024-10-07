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
int n, s;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
cc_hash_table<ll, int, chash> table;

int32_t main() {
    fast_cin();
    cin >> n >> s;
    s *= 2;
    vector<ar<ll, 2>> p(n);
    vector<ll> v;
    vector<int> div;
    for (auto& [x, y] : p) {
        cin >> x >> y;
        v.push_back(x * mxN + y);
    }
    sort(all(v));
    vector<int> cnt;
    for (int i = 0, j = 0; i < n; ) {
        while (j < n && v[i] == v[j])
            ++j;
        cnt.push_back(j - i);
        i = j;
    }
    v.erase(unique(all(v)), v.end());
    for (int i = 0; i < v.size(); ++i) {
        table[v[i]] = cnt[i];
    }
    // dbg(cnt);
    for (int i = 1; i <= s; ++i) {
        if (s % i == 0)
            div.push_back(i);
    }
    auto find = [&](ll x, ll y) -> ll {
        ll hh = x * mxN + y;
        // int it = lower_bound(all(v), hh) - v.begin();
        // if (it < v.size() && v[it] == hh)
        //     return cnt[it];
        // return 0;
        if (table.find(hh) != table.end())
            return table[hh];
        return 0;
        };
    ll ans = 0;
    for (auto [x, y] : p) {
        for (int j1 : div) {
            int j2 = s / j1;
            ans += (find(x - j1, y) + find(x + j1, y)) *
                (find(x, y - j2) + find(x, y + j2));
        }
    }
    cout << ans;
    return 0;
}