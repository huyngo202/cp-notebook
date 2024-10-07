#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
typedef long long ll;
#define ln "\n"
#define dbg(x) cout<<#x<<" = "<<x<<ln
#define pb push_back
#define INF 2e18
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define sz(x) ((ll)(x).size())
#define ar array
 
const int mxN = 1e6;
const ll MOD = 998244353, M = 1e9 + 7;
int n;
 
struct Point<double> {
    ll x, y, id;
    bool operator < (const Point<double>& b) {
        return (x == b.x) ? y < b.y : x < b.x;
    }
};
 
struct cmp {
    bool operator () (const Point<double>& a, const Point<double>& b) const {
        return (a.y == b.y) ? a.x < b.x : a.y < b.y;
    }
};
 
ll dist(Point<double> a, Point<double> b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
 
set<Point<double>, cmp> T;
vector<Point<double>> Point<double>s;
 
int32_t main() {
    fast_cin();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x, y; cin >> x >> y;
        Point<double>s.push_back({ x, y, i });
    }
 
    ll res_id1 = 1, res_id2 = 2;
    ll square_d = dist(Point<double>s[0], Point<double>s[1]);
    sort(all(Point<double>s));
    for (auto p : Point<double>s) {
        ll x = p.x, y = p.y, id = p.id, d = sqrt(square_d);
        Point<double> cur = { -100000000, y - d, id };
        while (true) {
            auto it = T.upper_bound(cur);
            if (it == T.end()) break;
            cur = *it;
            if (cur.y > y + d) break;
            if (cur.x < x - d) {
                T.erase(it);
                continue;
            }
            if (dist(p, cur) < square_d) {
                square_d = dist(p, cur);
            }
        }
        T.insert(p);
    }
 
    cout << square_d;
    return 0;
}