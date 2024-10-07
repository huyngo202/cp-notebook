//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>  
using namespace std;
void __print(int x) { cerr << x; } void __print(long x) { cerr << x; } void __print(long long x) { cerr << x; } void __print(unsigned x) { cerr << x; } void __print(unsigned long x) { cerr << x; } void __print(unsigned long long x) { cerr << x; } void __print(float x) { cerr << x; } void __print(double x) { cerr << x; } void __print(long double x) { cerr << x; } void __print(char x) { cerr << '\'' << x << '\''; } void __print(const char* x) { cerr << '"' << x << '"'; } void __print(const string& x) { cerr << '"' << x << '"'; } void __print(bool x) { cerr << (x ? "true" : "false"); } template<typename T, typename V> void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } template<typename T> void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; } void _print() { cerr << "]\n"; } template <typename T, typename... V> void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
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

const double eps = 1e-9;
#define double long double
int gauss(vector<vector<double>> a,
    vector<double>& ans) {
    int n = (int)a.size(); // số phương trình
    int m = (int)a[0].size() - 1; // số ẩn
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int e = row;
        for (int i = row + 1; i < n; i++) {
            if (abs(a[i][col]) >
                abs(a[e][col])) { // chọn phương trình e
                // có abs(a[e][col]) lớn nhất
                e = i;
            }
        }
        if (abs(a[e][col]) < eps) // tất cả các hệ số a[e][col] đều
            // bằng 0
            // => ẩn x[col] là ẩn tự do
            continue; // chuyển sang khử x[col + 1]
        swap(a[e], a[row]); // chuyển phương trình e lên đầu
        where[col] = row; // ẩn x[col] được khử bởi phương trình
        // đang ở vị trí row
        /* chuyển hệ số a[row][col] về 1 */
        double tmp = a[row][col];
        for (int i = 0; i <= m; i++) {
            a[row][i] /= tmp;
        }
        /* khử hệ số a[i][col] ở toàn bộ n - 1 phương
        * trình còn lại */
        for (int i = 0; i < n; i++) {
            if (i != row) {
                double c = a[i][col];
                for (int j = col; j <= m;
                    j++) { // chỉ cần for từ col tại vì
                    // a[row][p] (p < col) đã bằng 0
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        row++; // phương trình ở vị trí row đã được sử dụng
    }
    ans.assign(m, 0); // gán tất cả các ẩn ban đầu 0
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m]; // nếu x[i] không phải ẩn tự do thì
            // x[i] = b[where[i]]
        }
    }
    /* Thử lại */
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < m; j++) {
            sum += ans[j] * a[i][j];
        }
        if (abs(sum - a[i][m]) > eps) // sum != b[i]
            return 0;
    }
    for (int i = 0; i < m; i++)
        if (where[i] == -1) // nếu có ít nhất 1 ẩn tự do thì
            return 2; // hệ có vô số nghiệm
    return 1;
}

int32_t main() {
    fast_cin();
    int n, m;
    cin >> n >> m;
    vector<vector<double>> a(n, vector<double>(m + 1));
    vector<double> ans;
    rep(i, 0, n - 1)
        rep(j, 0, m)
        cin >> a[i][j];
    // cout << fixed << setprecision(15);

    int no = gauss(a, ans);
    cout << no << ln;
    if (no != 0) {
        for (double i : ans)
            printf("%.15Lf ", i);
    }
    return 0;
}