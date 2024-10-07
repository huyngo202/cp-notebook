#include <bits/stdc++.h>  
using namespace std;
using ll = long long;
using i64 = long long;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ln "\n"
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define ar array
int Bit(int mask, int b) { return (mask >> b) & 1; }
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1e6 + 5;
int n;

#define emb emplace_back
#define sz(x) (int)(x).size()
template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
using vi = vector<int>;
struct Edge { int u, v, w; };
struct Node {
    int v, h; ll w;
    Node* ls, * rs;
    Node(int v, ll w) : v(v), h(1), w(w), ls(0), rs(0) {}
};
Node* merge(Node* u, Node* v) {
    if (!u) return v;
    if (!v) return u;
    if (u->w > v->w) swap(u, v);
    Node* p = new Node(*u);
    p->rs = merge(u->rs, v);
    if (p->rs && (!p->ls || p->ls->h < p->rs->h)) swap(p->ls, p->
        rs);
    p->h = (p->rs ? p->rs->h : 0) + 1;
    return p;
}
vector<ll> k_shortest_paths(int N, const vector<Edge>& edges,
    int S, int T, int K) {
    vector<vi> G(N);
    rep(i, 0, sz(edges) - 1) G[edges[i].v].emb(i);
    min_heap<pair<ll, int>> pq;
    vector<ll> d(N, -1); vi done(N), par(N, -1), p;
    pq.emplace(d[T] = 0, T);
    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        if (done[u]) continue;
        p.emb(u); done[u] = 1;
        for (int i : G[u]) {
            auto [v, _, w] = edges[i];
            if (d[v] == -1 || d[v] > d[u] + w) {
                par[v] = i;
                pq.emplace(d[v] = d[u] + w, v);
            }
        }
    }
    if (d[S] == -1) return vector<ll>(K, -1);
    vector<Node*> heap(N);
    rep(i, 0, sz(edges) - 1) {
        auto [u, v, w] = edges[i];
        if (~d[u] && ~d[v] && par[u] != i)
            heap[u] = merge(heap[u], new Node(v, d[v] + w - d[u]));
    }
    for (int u : p) if (u != T)
        heap[u] = merge(heap[u], heap[edges[par[u]].v]);
    min_heap<pair<ll, Node*>> q;
    if (heap[S]) q.emplace(d[S] + heap[S]->w, heap[S]);
    vector<ll> res = { d[S] };
    for (int i = 1; i < K && !q.empty(); ++i) {
        auto [w, node] = q.top(); q.pop(); res.emb(w);
        if (heap[node->v])
            q.emplace(w + heap[node->v]->w, heap[node->v]);
        for (auto s : { node->ls, node->rs })
            if (s) q.emplace(w + s->w - node->w, s);
    }
    res.resize(K, -1);
    return res;
}

int32_t main() {
    fastIO();
    return 0;
}