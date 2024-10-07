#include <bits/stdc++.h>  
using namespace std;


template<
    class Val = long long,   // values stored in Trie
    class Count = long long, // frequency of values
    int B = (sizeof(Val) * 8 - 1)  // max number of bit
> struct BinaryTrie {
    struct Node {
        std::array<int, 2> child;
        Count count;
        Node() : child{ -1, -1 }, count(0) {}
    };

    BinaryTrie() : nodes{ Node() } {} // create root node

    // Number of elements in the trie
    Count size() {
        return nodes[0].count;
    }

    void insert(Val x, Count cnt = 1) {
        update(x, cnt);
    }
    void remove(Val x, Count cnt = 1) {
        update(x, -cnt);
    }

    // return min(X ^ xor_val)
    pair<Val, Node> min_element(Val xor_val = 0) {
        assert(0 < size());
        return kth_element(0, xor_val);
    }

    // Tested: https://www.spoj.com/problems/XORX/
    // return max(X ^ xor_val)
    pair<Val, Node> max_element(Val xor_val = 0) {
        assert(0 < size());
        return kth_element(size() - 1, xor_val);
    }

    // return k-th smallest (X ^ xor_val)  (0 <= K < size())
    pair<Val, Node> kth_element(Count k, Val xor_val = 0) {
        assert(0 <= k && k < size());
        int u = 0;
        Val x = 0;
        for (int i = B - 1; i >= 0; i--) {
            int b = get_bit(xor_val, i);
            int v0 = get_child(u, b);
            if (nodes[v0].count <= k) {
                k -= nodes[v0].count;
                u = get_child(u, 1 - b);
                x |= 1LL << i;
            }
            else {
                u = v0;
            }
        }
        return { x, nodes[u] };
    }

    // return frequency of x
    Count count(Val x) {
        int u = 0;
        for (int i = B - 1; i >= 0; i--) {
            int b = get_bit(x, i);
            if (nodes[u].child[b] == -1) {
                return 0;
            }
            u = get_child(u, b);
        }
        return nodes[u].count;
    }

    // Tested: https://www.spoj.com/problems/SUBXOR/
    // return how many values a where a ^ xor_val < x
    Count count_less_than(Val x, Val xor_val = 0) {
        Count sum = 0;
        int u = 0;
        for (int i = B - 1; i >= 0; --i) {
            int bx = get_bit(x, i);
            int bxor = get_bit(xor_val, i);
            if (bx == 1) {
                // i = first bit where a^xor_val differ from x
                if (nodes[u].child[bxor] >= 0) {
                    sum += nodes[nodes[u].child[bxor]].count;
                }
            }
            if (nodes[u].child[bx ^ bxor] == -1) {
                return sum;
            }
            u = get_child(u, bx ^ bxor);
        }
        return sum;
    }

    // private:
    vector<Node> nodes;

    int get_child(int p, int b) {
        assert(0 <= p && p < (int)nodes.size());
        assert(0 <= b && b < 2);
        if (nodes[p].child[b] == -1) {
            nodes[p].child[b] = nodes.size();
            nodes.push_back(Node{});
        }
        return nodes[p].child[b];
    }

    void update(Val x, Count cnt) {
        int u = 0;
        for (int i = B - 1; i >= 0; i--) {
            nodes[u].count += cnt;
            assert(nodes[u].count >= 0);  // prevent over delete
            int b = get_bit(x, i);
            u = get_child(u, b);
        }
        nodes[u].count += cnt;
        assert(nodes[u].count >= 0);  // prevent over delete
    }

    inline int get_bit(Val v, int bit) {
        return (v >> bit) & 1;
    }
};


// pointer implement
struct node {
    node* child[2];
    int cnt = 0;
    node() {
        for (int i = 0; i < 2; ++i) child[i] = NULL;
        cnt = 0;
    }
};
struct binaryTrie {
    static const int B = 17;
    node* root = new node();
    int size() {
        return root->cnt;
    }
    void insert(int x, int count = 1) {
        node* p = root;
        p->cnt += count;
        for (int i = B - 1; i >= 0; --i) {
            int b = x >> i & 1;
            if (p->child[b] == NULL)
                p->child[b] = new node();
            p = p->child[b];
            p->cnt += count;
        }
    }
    void remove(int x, int count, int i, node* p) {
        if (i < 0)
            return;
        int d = x >> i & 1;
        p->child[d]->cnt -= count;
        remove(x, count, i - 1, p->child[d]);
        if (p->child[d]->cnt == 0) {
            p->child[d] = NULL;
            delete(p->child[d]);
        }
    }
    void remove(int x, int count = 1) {
        remove(x, count, B - 1, root);
    }
    // count < x
    int count_less_than(int x) {
        int res = 0;
        node* p = root;
        for (int i = B - 1; i >= 0; --i) {
            int b = x >> i & 1;
            if (b == 1) {
                if (p->child[0])
                    res += p->child[0]->cnt;
            }
            if (p->child[b] == NULL)
                return res;
            p = p->child[b];
        }
        return res;
    }
    // 1 <= k <= size
    int k_th(int k) {
        assert(1 <= k && k <= size());
        node* p = root;
        int res = 0;
        for (int i = B - 1; i >= 0; --i) {
            if (p->child[0] && p->child[0]->cnt >= k)
                p = p->child[0];
            else {
                res |= 1 << i;
                if (p->child[0])
                    k -= p->child[0]->cnt;
                p = p->child[1];
            }
        }
        return res;
    }
};

int32_t main() {

    return 0;
}