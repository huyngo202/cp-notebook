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

struct Node {
    int x;
    Node* l = 0;
    Node* r = 0;
    Node* p = 0;
    bool rev = false;

    Node() = default;

    Node(int v) { x = v; }

    void push() {
        if (rev) {
            rev = false;
            swap(l, r);
            if (l) l->rev ^= true;
            if (r) r->rev ^= true;
        }
    }

    bool is_root() { return p == 0 || (p->l != this && this != p->r); }
};

struct LCT {
    vector<Node> a;

    LCT(int n) {
        a.resize(n + 1);
        for (int i = 1; i <= n; ++i) a[i].x = i;
    }

    void rot(Node* c) {
        auto p = c->p;
        auto g = p->p;

        if (!p->is_root()) (g->r == p ? g->r : g->l) = c;

        p->push();
        c->push();

        if (p->l == c) {  // rtr
            p->l = c->r;
            c->r = p;
            if (p->l) p->l->p = p;
        }
        else {  // rtl
            p->r = c->l;
            c->l = p;
            if (p->r) p->r->p = p;
        }

        p->p = c;
        c->p = g;
    }

    void splay(Node* c) {
        while (!c->is_root()) {
            auto p = c->p;
            auto g = p->p;
            if (!p->is_root()) rot((g->r == p) == (p->r == c) ? p : c);
            rot(c);
        }
        c->push();
    }

    Node* access(int v) {
        Node* last = 0;
        Node* c = &a[v];
        for (Node* p = c; p; p = p->p) {
            splay(p);
            p->r = last;
            last = p;
        }
        splay(c);
        return last;
    }

    void make_root(int v) {
        access(v);
        auto* c = &a[v];
        if (c->l) c->l->rev ^= true, c->l = 0;
    }

    void link(int u, int v) {
        if (connected(u, v)) return;
        make_root(v);
        Node* c = &a[v];
        c->p = &a[u];
    }

    void cut(int u, int v) {
        if (!connected(u, v))
            return;
        make_root(u);
        access(v);
        if (a[v].l) {
            a[v].l->p = 0;
            a[v].l = 0;
        }
    }

    bool connected(int u, int v) {
        access(u);
        access(v);
        return a[u].p;
    }
};

const int mxN = 5e4 + 5;
int n, m;

int32_t main() {
    fast_cin();
    int m;
    cin >> n >> m;
    LCT T(n + 1);
    string q;
    int u, v;
    rep(i, 1, m) {
        cin >> q >> u >> v;
        if (q == "conn")
            cout << (T.connected(u, v) ? "YES\n" : "NO\n");
        else if (q == "add")
            T.link(u, v);
        else
            T.cut(u, v);
    }
    return 0;
}