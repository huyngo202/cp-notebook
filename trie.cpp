#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(int x) { cerr << x; } void __print(long int x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ll long long
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define siz(x) ((ll)(x).size())
#define ar array
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

const int mxN = 1e6 + 5;
int n;
struct node {
    node* child[2];
    int cnt;
    node() {
        rep(i, 0, 1) child[i] = NULL;
        cnt = 0;
    }
};
node* root = new node();

void ins(int x) {
    node* p = root;
    for (int i = 30; i >= 0; --i) {
        int d = x >> i & 1;
        if (p->child[d] == NULL)
            p->child[d] = new node();
        p = p->child[d];
        p->cnt++;
    }
}

int qry(int x, int l) {
    node* p = root;
    int ans = 0;
    for (int i = 30; i >= 0; --i) {
        int d = l >> i & 1;
        int xr = x >> i & 1;
        if (d == 0) {
            if (xr == 1)
                p = p->child[1];
            else
                p = p->child[0];
        }
        else {
            // d == 1
            if (xr == 1) {
                if (p->child[1])
                    ans += p->child[1]->cnt;
                p = p->child[0];
            }
            else {
                if (p->child[0])
                    ans += p->child[0]->cnt;
                p = p->child[1];
            }
        }
        if (p == NULL) return ans;
    }
    return ans;
}

void rem(int x, int i = 30, node* p = root) {
    if (i < 0)
        return;
    int d = x >> i & 1;
    --p->child[d]->cnt;
    rem(x, i - 1, p->child[d]);
    if (p->child[d]->cnt == 0)
        p->child[d] = NULL;
}

int32_t main() {
    fast_cin();
    cin >> n;
    int qt, u, v;
    rep(i, 1, n) {
        cin >> qt;
        if (qt == 1) {
            cin >> u;
            ins(u);
        }
        else if (qt == 2) {
            cin >> u;
            rem(u);
        }
        else {
            cin >> u >> v;
            // x xor u < v
            cout << qry(u, v) << ln;
        }
    }
    return 0;
}