#include <bits/stdc++.h>  
using namespace std;
#define ln "\n"

int n;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
using oset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

oset<char> s;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    s.insert('a');
    s.insert('c');
    cout << s.order_of_key('b' + 1);
    return 0;
}