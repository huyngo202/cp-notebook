//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#define ln "\n"
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define ar array
using ll = long long;
int Bit(int mask, int b) { return (mask >> b) & 1; }
const ll base = 311, MOD = 998244353, M = 1e9 + 7, INF = 1e18;

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
    // angle to x−axis in interval [−pi , pi ]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist() = 1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated ’a ’ radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<ll> P;
void __print(P p) { cerr << "(" << p.x << " " << p.y << ")"; }

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
    return (double)(b - a).cross(p - a) / (b - a).dist();
}

// Usage: Point<double> a, b(2, 2), p(1, 1);
// bool onSegment = segDist(a, b, p) < 1e-10;
// typedef Point<double> P;
// double segDist(P& s, P& e, P& p) {
//     if (s == e) return (p - s).dist();
//     auto d = (e - s).dist2();
//     auto t = min((double)d, max(.0, (double)(p - s).dot(e - s)));
//     return ((p - s) * d - (e - s) * t).dist() / d;
// }

// usage:
// vector<P> inter = segInter(s1, e1, s2, e2);
// if (sz(inter) == 1)
// cout << "segments intersect at " << inter[0] << endl;
template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
        oc = a.cross(b, c), od = a.cross(b, d);
    // Checks i f intersection is single non−endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return { (a * ob - b * oa) / (ob - oa) };
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return { all(s) };
}

// Usage: auto res = lineInter(s1, e1, s2, e2);
// if (res.first == 1)
// cout << "intersection point at " << res.second << endl;
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return { -(s1.cross(e1, s2) == 0), P(0, 0) };
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return { 1, (s1 * p + e1 * q) / d };
}

// Usage: bool left = sideOf(p1, p2, q) == 1;
template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}

// Description: Returns true if p lies on the line segment from s to e.
// Use (segDist(s, e, p) <= epsilon) instead when using Point<double>.
template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

// Usage: vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
// bool in = inPolygon(v, P{3, 3}, false);
template<class P>
bool inPolygon(vector<P>& p, P a, bool strict = true) {
    int cnt = 0, n = (int)p.size();
    rep(i, 0, n) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a)) return !strict;
        //or : i f (segDist(p[ i ] , q , a) <= eps) return ! s t r i c t ;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}

typedef Point<ll> P;
bool inHull(const vector<P>& l, P p, bool strict = false) {
    int a = 1, b = (int)l.size() - 1, r = !strict;
    if ((int)l.size() < 3) return r && onSegment(l[0], l.back(), p);
    if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
    if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}

// 2xarea
template<class T>
T polygonArea2(vector<Point<T>>& v) {
    T a = v.back().cross(v[0]);
    for (int i = 0; i < (int)v.size() - 1; ++i)
        a += v[i].cross(v[i + 1]);
    return a;
}

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
    if ((int)pts.size() <= 1) return pts;
    sort(all(pts));
    vector<P> h(pts.size() + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (P p : pts) {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
            h[t++] = p;
        }
    return { h.begin(), h.begin() + t - (t == 2 && h[0] == h[1]) };
}

const int mxN = 1e6 + 5;
int n;

int32_t main() {
    fast_cin();
    cin >> n;
    vector<P> v(n);
    rep(i, 0, n - 1)
        cin >> v[i].x >> v[i].y;
    vector<P> h = convexHull(v);

    int q; cin >> q;
    rep(_, 1, q) {
        P p; cin >> p.x >> p.y;
        bool f = inHull(h, p);
        cout << (f ? "YES\n" : "NO\n");
    }
    return 0;
}
