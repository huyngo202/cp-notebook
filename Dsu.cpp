#include <bits/stdc++.h>  
using namespace std;
#define ll long long
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define rep(i,a,b) for(int i=a; i<=b; ++i)

const int mxN = 1e6 + 2;

struct Dsu {
    int s[mxN], par[mxN];
    void init(int n) { rep(i, 0, n) s[i] = 1, par[i] = i; }
    int find(int i) { return par[i] == i ? i : par[i] = find(par[i]); }
    int size(int i) { return s[find(i)]; }
    bool same(int u, int v) { return find(u) == find(v); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (s[a] < s[b]) swap(a, b);
        s[a] += s[b]; par[b] = a;
        return true;
    }
};
Dsu T;

struct DSU {
    std::vector<int> f, siz;
    DSU() {}
    DSU(int n) { init(n); }
    void init(int n) {
        f.resize(++n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return siz[find(x)]; }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y]; f[y] = x;
        return true;
    }
};

// Usage: int t = uf.time(); ...; uf.rollback(t);
struct RollbackUF {
    vector<int> e; vector<pair<int, int>> st;
    RollbackUF(int n = 1) : e(n + 1, -1) {}
    void init(int n) { e.assign(n + 1, -1); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return st.size(); }
    void rollback(int t) {
        for (int i = time(); i-- > t;)
            e[st[i].first] = st[i].second;
        st.resize(t);
    }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (e[u] > e[v]) swap(u, v);
        st.emplace_back(u, e[u]); st.emplace_back(v, e[v]);
        e[u] += e[v]; e[v] = u;
        return true;
    }
};


int32_t main() {
    fast_cin();
    return 0;
}