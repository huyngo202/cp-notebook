#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(int x) { cerr << x; } void __print(long int x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); }
template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
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

struct node {
    int mn, s;
}st[mxN * 4];

void upd(int l1, int x, int i = 1, int l2 = 0, int r2 = m - 1) {
    if (l2 == r2) {
        st[i].mn = x;
        st[i].s = x;
        return;
    }
    int m2 = (l2 + r2) / 2;
    if (l1 <= m2)
        upd(l1, x, i * 2, l2, m2);
    else
        upd(l1, x, i * 2 + 1, m2 + 1, r2);
    st[i].mn = min(st[i * 2].mn, st[i * 2 + 1].mn);
    st[i].s = st[i * 2].s + st[i * 2 + 1].s;
}

int qry(int l1, int r1, int i = 1, int l2 = 0, int r2 = m - 1) {
    if (l1 > r2 || l2 > r1) return n;
    if (l1 <= l2 && r2 <= r1)
        return st[i].mn;
    int m2 = (l2 + r2) / 2;
    return min(qry(l1, r1, i * 2, l2, m2),
        qry(l1, r1, i * 2 + 1, m2 + 1, r2));
}

struct node {
    ll mn, mx, s, lz;
};

struct lazy_segment_tree {
    node st[mxN];
    node merge(const node& a, const node& b) {
        node r = { min(a.mn, b.mn),
                    max(a.mx, b.mx),
                    a.s + b.s
        };
        return r;
    }

    void app(int i, ll x, int l2, int r2) {
        st[i].mn += x;
        st[i].mx += x;
        st[i].s += (r2 - l2 + 1) * x;
        st[i].lz += x;
    }

    void push(int i, int l2, int m2, int r2) {
        app(i * 2, st[i].lz, l2, m2);
        app(i * 2 + 1, st[i].lz, m2 + 1, r2);
        st[i].lz = 0;
    }

    void upd(int l1, ll x, int i = 1, int l2 = 1, int r2 = n) {
        if (l2 == r2) {
            st[i].mx = st[i].mn = st[i].s = x;
            return;
        }
        int m2 = (l2 + r2) / 2;
        if (l1 <= m2)
            upd(l1, x, i * 2, l2, m2);
        else
            upd(l1, x, i * 2 + 1, m2 + 1, r2);
        st[i] = merge(st[i * 2], st[i * 2 + 1]);
    }

    void upd2(int l1, int r1, ll x, int i = 1, int l2 = 1, int r2 = n) {
        if (l1 <= l2 && r2 <= r1) {
            app(i, x, l2, r2);
            return;
        }
        int m2 = (l2 + r2) / 2;
        push(i, l2, m2, r2);
        if (l1 <= m2)
            upd2(l1, r1, x, i * 2, l2, m2);
        if (m2 < r1)
            upd2(l1, r1, x, i * 2 + 1, m2 + 1, r2);
        st[i] = merge(st[i * 2], st[i * 2 + 1]);
    }

    ll qry(int l1, int r1, int i = 1, int l2 = 1, int r2 = n) {
        if (l1 <= l2 && r2 <= r1)
            return st[i].s;
        int m2 = (l2 + r2) / 2;
        push(i, l2, m2, r2);
        // return min(l1<=m2? qry(l1, r1, i*2, l2, m2):oo, m2<r1? qry(l1, r1, i*2+1, m2+1, r2):oo);
        return ((l1 <= m2) ? qry(l1, r1, i * 2, l2, m2) : 0) + ((m2 < r1) ? qry(l1, r1, i * 2 + 1, m2 + 1, r2) : 0);
    }
};

int main() {
    int q, x;
    cin >> n >> q;
    rep(i, 1, n) {
        cin >> x;
        upd(i, x);
    }
    int a, b, qt;
    while (q--) {
        cin >> qt;
        if (qt == 1) {
            ll w;
            cin >> a >> b >> w;
            upd2(a, b, w);
        }
        else {
            cin >> a;
            cout << qry(a, a) << ln;
        }
    }
    return 0;
}