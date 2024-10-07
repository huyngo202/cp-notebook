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
int n, q;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x−axis in interva l [−pi , pi ]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes d is t ()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated ’a ’ radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << p.x << " " << p.y;
    }
    friend bool operator < (Point u, Point v) {
        return u.x < v.x || (u.x == v.x && u.y < v.y);
    }
};
typedef Point<ll> P;
void __print(P p) { cerr << "(" << p.x << "," << p.y << ")"; }

// wana as much points possible modify cross >= 0 -> cross > 0
vector<P> convex(vector<P>& p) {
    vector<P> hull;
    rep(i, 0, n - 1) {
        while (hull.size() >= 2 &&
            (hull.end()[-1] - hull.end()[-2]).
            cross(p[i] - hull.end()[-1]) >= 0)
            hull.pop_back();
        hull.push_back(p[i]);
    }
    int lower_sz = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() > lower_sz &&
            (hull.end()[-1] - hull.end()[-2]).
            cross(p[i] - hull.end()[-1]) >= 0)
            hull.pop_back();
        hull.push_back(p[i]);
    }
    hull.pop_back();
    return hull;
}

int32_t main() {
    fast_cin();
    cin >> n;
    vector<P> v(n);
    for (auto& p : v)
        cin >> p.x >> p.y;
    sort(all(v));
    vector<P> hull = convex(v);
    cout << hull.size() << ln;
    for (auto p : hull)
        cout << p << ln;
    return 0;
}