//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define siz(x) ((ll)(x).size())
#define ar array
using ll = long long;
int Bit(int mask, int b) { return (mask >> b) & 1; }
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1e5 + 5;
int n;

struct node {
    int cnt, s;
}st[mxN * 4];

void upd(int l1, int r1, int x, int i = 1, int l2 = 0, int r2 = mxN - 5) {
    if (l1 > r2 || l2 > r1) return;
    if (l1 <= l2 && r2 <= r1) {
        st[i].cnt += x;
    }
    else {
        int m2 = (l2 + r2) / 2;
        upd(l1, r1, x, i * 2, l2, m2);
        upd(l1, r1, x, i * 2 + 1, m2 + 1, r2);
    }
    if (st[i].cnt == 0)
        st[i].s = st[i * 2].s + st[i * 2 + 1].s;
    else
        st[i].s = r2 - l2 + 1;
}

int32_t main() {
    fast_cin();

    vector<ar<int, 4>> events;
    cin >> n;
    rep(i, 1, n) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back({ x1, y1, y2, 1 });
        events.push_back({ x2, y1, y2, -1 });
    }
    sort(all(events));

    int res = 0;
    rep(i, 0, events.size() - 2) {
        auto [x, y1, y2, e] = events[i];
        upd(y1, y2 - 1, e);
        res += (events[i + 1][0] - x) * st[1].s;
    }
    cout << res;
    return 0;
}