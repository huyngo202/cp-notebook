#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define ar array
using ll = long long;
int Bit(int mask, int b) { return (mask >> b) & 1; }
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1.5e6 + 1;

struct node {
    ll cnt, s;
}st[mxN * 4];
// compress y-axis
vector<ll> ys;
ll lo[mxN * 4], hi[mxN * 4];
vector<ar<ll, 4>> events;

void build(int i = 1, int l = 0, int r = ys.size() - 2) {
    if (l == r) {
        lo[i] = ys[l];
        hi[i] = ys[l + 1];
        // dbg(i, lo[i], hi[i]);
        return;
    }
    int m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m + 1, r);
    lo[i] = lo[i * 2];
    hi[i] = hi[i * 2 + 1];
    // dbg(i, lo[i], hi[i]);
}

void upd(ll l1, ll r1, int x, int i = 1) {
    if (l1 > hi[i] || lo[i] > r1) return;
    if (l1 <= lo[i] && hi[i] <= r1)
        st[i].cnt += x;
    else {
        upd(l1, r1, x, i * 2);
        upd(l1, r1, x, i * 2 + 1);
    }
    if (st[i].cnt)
        st[i].s = hi[i] - lo[i];
    else
        st[i].s = st[i * 2].s + st[i * 2 + 1].s;
}

// lower-left; upper-right
ll solve(const vector<ar<ll, 4>> rect) {
    for (auto [x1, y1, x2, y2] : rect) {
        ys.push_back(y1);
        ys.push_back(y2);
        events.push_back({ x1, y1 , y2, 1 });
        events.push_back({ x2, y1 , y2, -1 });
    }
    sort(all(events));
    sort(all(ys));
    ys.erase(unique(all(ys)), ys.end());
    build();

    // dbg(ys);
    ll res = 0;
    for (int i = 0; i < (int)events.size() - 1; ++i) {
        auto [x, y1, y2, e] = events[i];
        // dbg(y1, y2, e);
        upd(y1, y2, e);
        res += (events[i + 1][0] - x) * st[1].s;
        // dbg(res);
    }
    return res;
}

int32_t main() {
    fast_cin();
    int n;
    cin >> n;
    vector<ar<ll, 4>> rect;
    rep(i, 1, n) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rect.push_back({ x1,y1,x2,y2 });
    }
    cout << solve(rect);
    return 0;
}