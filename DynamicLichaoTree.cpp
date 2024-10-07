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

template<typename T, T minX, T maxX, T defVal, bool maximum>
struct DynamicLiChaoTree {
private:
    struct Line {
        T a, b;
        inline T calc(T x) const { return a * x + b; }
    };
    struct Node {
        Line line = { 0, maximum ? defVal : -defVal };
        Node* lt = nullptr, * rt = nullptr;
    } *root;
    void update(Node* cur, T l, T r, T u, T v, Line nw) {
#define newNode(x) if (!x) x = new Node()
        if (v < l || r < u) return;
        T mid = (l + r) >> 1;
        if (u <= l && r <= v) {
            if (cur->line.calc(l) >= nw.calc(l)) swap(cur->line, nw);
            if (cur->line.calc(r) <= nw.calc(r)) {
                cur->line = nw; return;
            }
            if (nw.calc(mid) >= cur->line.calc(mid)) {
                newNode(cur->rt);
                update(cur->rt, mid + 1, r, u, v, cur->line);
                cur->line = nw;
            }
            else {
                newNode(cur->lt);
                update(cur->lt, l, mid, u, v, nw);
            }
        }
        else {
            newNode(cur->lt); newNode(cur->rt);
            update(cur->lt, l, mid, u, v, nw);
            update(cur->rt, mid + 1, r, u, v, nw);
        }
#undef newNode
    }
public:
    DynamicLiChaoTree() { root = new Node(); }
    void add(T a, T b, T l = minX, T r = maxX) {
        if (!maximum) a = -a, b = -b;
        update(root, minX, maxX, l, r, { a, b });
    }
    T query(T x) {
        Node* cur = root;
        T res = cur->line.calc(x), l = minX, r = maxX, mid;
        while (cur) {
            res = max(res, cur->line.calc(x));
            mid = (l + r) >> 1;
            if (x <= mid) cur = cur->lt, r = mid;
            else cur = cur->rt, l = mid + 1;
        }
        return maximum ? res : -res;
    }
};

const int mxN = 1e5 + 5;
int n, q;

int32_t main() {
    fast_cin();
    DynamicLiChaoTree<ll, -M + 7LL, M - 7LL, INF + 13, false> T;
    cin >> n >> q;
    rep(i, 1, n) {
        ll l, r, a, b;
        cin >> l >> r >> a >> b;
        T.add(a, b, l, r - 1);
    }
    rep(_, 1, q) {
        ll qr, l, r, a, b;
        cin >> qr;
        if (qr == 0) {
            cin >> l >> r >> a >> b;
            T.add(a, b, l, r - 1);
        }
        else {
            cin >> a;
            ll ans = T.query(a);
            if (ans == INF + 13)
                cout << "INFINITY\n";
            else
                cout << ans << ln;
        }
    }
    return 0;
}