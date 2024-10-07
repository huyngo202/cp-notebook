#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
#define ll long long
#define ln "\n"
#define dbg(x) cout<<#x<<" = "<<x<<ln
#define pb push_back
#define INF 2e18
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define sz(x) ((ll)(x).size())
#define ar array

const ll base = 311;
const ll MOD = 998244353, M = 1e9 + 7;
const int mxN = 1e6 + 5;

struct TrieBit {
    const int LG = 30;
    struct node {
        node* child[2];
        ll cnt, mx, mn, s, end;
        node() {
            rep(i, 0, 1)
                child[i] = NULL;
            cnt = mx = mn = s = 0;
        }
    };
    node* root = new node();
    void ins(ll x) {
        node* p = root;
        for (int i = LG; ~i; --i) {
            int c = x >> i & 1;
            if (p->child[c] == NULL)
                p->child[c] = new node();
            p = p->child[c];
            p->s += x;
            ++p->cnt;
            p->mn = min(p->mn, x);
            p->mx = max(p->mx, x);
            p->s += x;
        }
        ++p->end;
    }

    ll findkth(int k) {
        ll ans = 0;
        node* p = root;
        while (true) {
            if (p->end >= k) break;
            k -= p->end;
            rep(i, 0, 1) {
                if (p->child[i]) {
                    if (p->child[i]->cnt >= k) {
                        p = p->child[i];
                        break;
                    }
                }
                k -= p->cnt;
            }
        }
        return ans;
    }
}T;

int32_t main() {
    fast_cin();
    T.ins(4);
    T.ins(3);
    T.ins(8);
    cout << T.findkth(2);
    return 0;
}