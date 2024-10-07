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

const int mxN = 1e6 + 5;
int n;

const int inf = 1e9;
const bool PERSISTENT = false; // set to true for persistence
// Usage: Node* tr = new Node(v, 0, sz(v));
struct Node {
#define vi vector<int>
    Node* l = 0, * r = 0;
    int lo, hi, mset = inf, madd = 0, val = -inf;
    Node(int lo, int hi) :lo(lo), hi(hi) {} // Large interva l of −in f
    Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid); r = new Node(v, mid, hi);
            val = max(l->val, r->val);
        }
        else val = v[lo];
    }
    int query(int L, int R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
    Node* set(int L, int R, int x, bool persist = PERSISTENT) {
        if (R <= lo || hi <= L) return this;
        Node* res = persist ? new Node(*this) : this;
        if (L <= lo && hi <= R) {
            res->mset = res->val = x;
            res->madd = 0;
        }
        else {
            res->push();
            res->l = res->l->set(L, R, x), res->r = res->r->set(L, R, x);
            res->val = max(res->l->val, res->r->val);
        }
        return res;
    }
    Node* add(int L, int R, int x, bool persist = PERSISTENT) {
        if (R <= lo || hi <= L) return this;
        Node* res = persist ? new Node(*this) : this;
        if (L <= lo && hi <= R) {
            if (res->mset != inf) res->mset += x;
            else res->madd += x;

            res->val += x;
        }
        else {
            res->push();
            res->l = res->l->add(L, R, x), res->r = res->r->add(L, R, x);
            res->val = max(res->l->val, res->r->val);
        }
        return res;
    }
    void push() {
        bool nw = PERSISTENT;
        if (!l) {
            nw = false;
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
        if (mset != inf)
            l = l->set(lo, hi, mset, nw), r = r->set(lo, hi, mset, nw), mset = inf;
        else if (madd)
            l = l->add(lo, hi, madd, nw), r = r->add(lo, hi, madd, nw), madd = 0;
    }
};

struct node {
    ll mn, mx, s, lz;
}st[1 << 19];

void apply(int i, ll x, int l2, int r2) {
    st[i].mn += x;
    st[i].mx += x;
    st[i].s += (r2 - l2 + 1) * x;
    st[i].lz += x;
}

void push(int i, int l2, int m2, int r2) {
    apply(i * 2, st[i].lz, l2, m2);
    apply(i * 2 + 1, st[i].lz, m2 + 1, r2);
    st[i].lz = 0;
}

void modify(int l1, ll x, int i = 1, int l2 = 1, int r2 = n) {
    if (l2 == r2) {
        st[i].mn = x;
        st[i].s = x;
        st[i].mx = x;
        return;
    }
    int m2 = (l2 + r2) / 2;
    if (l1 <= m2)
        modify(l1, x, i * 2, l2, m2);
    else
        modify(l1, x, i * 2 + 1, m2 + 1, r2);
    st[i].mn = min(st[i * 2].mn, st[i * 2 + 1].mn);
    st[i].mx = max(st[i * 2].mx, st[i * 2 + 1].mx);
    st[i].s = st[i * 2].s + st[i * 2 + 1].s;
}

void rangeApply(int l1, int r1, ll x, int i = 1, int l2 = 1, int r2 = n) {
    if (l1 <= l2 && r2 <= r1) {
        apply(i, x, l2, r2);
        return;
    }
    int m2 = (l2 + r2) / 2;
    push(i, l2, m2, r2);
    if (l1 <= m2)
        rangeApply(l1, r1, x, i * 2, l2, m2);
    if (m2 < r1)
        rangeApply(l1, r1, x, i * 2 + 1, m2 + 1, r2);
    st[i].mn = min(st[i * 2].mn, st[i * 2 + 1].mn);
    st[i].mx = max(st[i * 2].mx, st[i * 2 + 1].mx);
    st[i].s = st[i * 2].s + st[i * 2 + 1].s;
}

ll query(int l1, int r1, int i = 1, int l2 = 1, int r2 = n) {
    if (l1 <= l2 && r2 <= r1)
        return st[i].s; // remember to modify this
    int m2 = (l2 + r2) / 2;
    push(i, l2, m2, r2);
    // return min(l1<=m2? query(l1, r1, i*2, l2, m2):oo, m2<r1? query(l1, r1, i*2+1, m2+1, r2):oo);
    // return max(l1<=m2? query(l1, r1, i*2, l2, m2):-oo, m2<r1? query(l1, r1, i*2+1, m2+1, r2):-oo);
    return ((l1 <= m2) ? query(l1, r1, i * 2, l2, m2) : 0) + ((m2 < r1) ? query(l1, r1, i * 2 + 1, m2 + 1, r2) : 0);
}

int32_t main() {
    fast_cin();
    return 0;
}