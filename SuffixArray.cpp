#include <bits/stdc++.h>  
using namespace std;


vector<int> suffix_array(const string& str) {
    string s = str + "$";
    int n = s.size();
    vector<int> p(n), c(n);
    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; ++i) a[i] = { s[i], i };
    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; ++i) c[p[i]] = c[p[i - 1]] + (a[i - 1].first < a[i].first);

    auto count_sort = [&]() -> void {
        vector<int> p_new(n), pos(n), cnt(n);
        for (int v : c) cnt[v]++;
        for (int i = 1; i < n; ++i) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; ++i) {
            int v = c[p[i]];
            p_new[pos[v]] = p[i];
            ++pos[v];
        }
        p = p_new;
        };

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; ++i) p[i] = (p[i] - k + n) % n;
        count_sort();
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            pair<int, int> prev = { c[p[i - 1]], c[(p[i - 1] + k) % n] };
            pair<int, int> now = { c[p[i]], c[(p[i] + k) % n] };
            c_new[p[i]] = c_new[p[i - 1]] + (prev < now);
        }
        c = c_new;
    }
    return p;
}

vector<int> lcp(const string& str) {
    string s = str + "$";
    auto sa = suffix_array(s);
    int n = s.size();
    vector<int> lcp(n), pos(n);
    for (int i = 0; i < n; ++i) pos[sa[i]] = i;
    int start_at = 0;
    for (int i = 0; i < n - 1; ++i) {
        int prev = sa[pos[i] - 1];
        int cmp = start_at;
        while (s[i + cmp] == s[prev + cmp])++cmp;
        lcp[pos[i]] = cmp;
        start_at = max(cmp - 1, 0);
    }
    return lcp;
}

vector<int> SA(const string& str) {
    string s = str + "$";
    int n = s.size();
    vector<int> p(n), c(n);
    vector<pair<pair<int, int>, int>> a(n);
    {
        for (int i = 0; i < n; ++i) a[i] = { {s[i], s[i]}, i };
        sort(a.begin(), a.end());
        for (int i = 0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i)
            c[p[i]] = c[p[i - 1]] + (a[i - 1].first < a[i].first);
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; ++i)
            a[i] = { {c[i], c[(i + k) % n]} , i };
        sort(a.begin(), a.end());
        for (int i = 0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i)
            c[p[i]] = c[p[i - 1]] + (a[i - 1].first < a[i].first);
    }
    return p;
}


int32_t main() {
    string s; cin >> s;
    auto c = suffix_array(s);
    for (int x : c)
        cout << x << " ";
    cout << endl;
    for (int x : SA(s))
        cout << x << " ";

    auto sa = suffix_array(s);
    s += "$";
    int n = s.size();
    int q; cin >> q;

    auto findFirst = [&](string x) -> int {
        int l = 0, r = n - 1, ok = 0, ret = INT_MAX;
        while (l <= r) {
            int m = (l + r) / 2;
            int i = 0, j = sa[m];
            for (; i < (int)x.size() && j < n; ++i, ++j)
                if (x[i] != s[j]) break;
            if (i == (int)x.size())
                ok = 1, r = m - 1, ret = min(ret, m);
            else if (x[i] < s[j])
                r = m - 1;
            else
                l = m + 1;
        }
        if (!ok) return -1;
        return ret;
        };

    auto findLast = [&](string x) -> int {
        int l = 0, r = n - 1, ok = 0, ret = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            int i = 0, j = sa[m];
            for (; i < (int)x.size() && j < n; ++i, ++j)
                if (x[i] != s[j]) break;
            if (i == (int)x.size())
                ok = 1, l = m + 1, ret = max(ret, m);
            else if (x[i] < s[j])
                r = m - 1;
            else
                l = m + 1;
        }
        if (!ok) return -1;
        return ret;
        };

    while (q--) {
        string x;
        cin >> x;
        int ok = findFirst(x);
        cout << (ok ? "Yes\n" : "No\n");
    }

    return 0;
}