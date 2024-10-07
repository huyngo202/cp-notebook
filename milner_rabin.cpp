#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(int x) { cerr << x; }
void __print(long int x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '"' << x << '"'; }
void __print(const string& x) { cerr << '"' << x << '"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)

#define ll long long
#define ln "\n"
#define pb push_back
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define sz(x) ((ll)(x).size())
#define ar array

const ll base = 311;
const ll MOD = 998244353, M = 1e9 + 7, INF = 2e18;
const int mxN = 1e6 + 5;
int n;

pair<ll, ll> factor(ll n) {
    ll s = 0;
    while ((n & 1) == 0) {
        s++;
        n >>= 1;
    }
    return { s, n };
}

ll pow(ll a, ll d, ll n) {
    ll result = 1;
    a = a % n;
    while (d > 0) {
        if (d & 1) result = result * a % n;
        d >>= 1;
        a = a * a % n;
    }
    return result;
}

bool test_a(ll s, ll d, ll n, ll a) {
    if (n == a) return true;
    ll p = pow(a, d, n);
    if (p == 1) return true;
    for (; s > 0; s--) {
        if (p == n - 1) return true;
        p = p * p % n;
    }
    return false;
}


bool miller(ll n) {
    if (n < 2) return false;
    if ((n & 1) == 0) return n == 2;
    ll s, d;
    tie(s, d) = factor(n - 1);
    return test_a(s, d, n, 2) && test_a(s, d, n, 3);
}

int32_t main() {
    fast_cin();
    ll t; cin >> t;
    for (int it = 1; it <= t; it++) {
        solve();
    }
    return 0;
}