#include<bits/stdc++.h>
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
int n;

vector<int> kmp(const string& s) {
    vector<int> z(s.size(), 0);
    int k = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        while (k && s[i] != s[k])
            k = z[k - 1];
        z[i] = s[i] == s[k] ? ++k : k;
    }
    return z;
}

vector<int> match(const string& p, const string s) {
    auto z = kmp(p + ")" + s);
    vector<int> res;
    // index of position from 0
    for (int i = (int)p.size(); i < (int)z.size(); ++i)
        if (z[i] == (int)p.size())
            res.push_back(i - 2 * p.size());
    return res;
}

int32_t main() {
    fast_cin();
    string s, p;
    cin >> s >> p;
    auto m = match(p, s);
    for (int i : m)
        cout << i + 1 << ' ';
    return 0;
}