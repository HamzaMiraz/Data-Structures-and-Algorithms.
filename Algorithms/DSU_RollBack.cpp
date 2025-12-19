#include <bits/stdc++.h>
using namespace std;

/**
 * DSU with Rollback logic:
 * We cannot use path compression because it permanently flattens the tree, 
 * which makes "undoing" operations impossible. Instead, we use Union by Size.
 */
struct DSURollback {
    struct Op {
        int v, u, prev_sz_u, prev_max_comp;
    };
    vector<int> parent, sz;
    vector<Op> history;
    int components;
    int max_comp_size;

    DSURollback(int n = 0) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        components = n;
        max_comp_size = (n > 0 ? 1 : 0);
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) {
            // Push a "no-op" to keep history synchronized with segment tree nodes
            history.push_back({-1, -1, -1, max_comp_size});
            return;
        }
        if (sz[a] < sz[b]) swap(a, b);

        // Record current state before merging
        history.push_back({b, a, sz[a], max_comp_size});

        parent[b] = a;
        sz[a] += sz[b];
        components--;
        max_comp_size = max(max_comp_size, sz[a]);
    }

    int snapshot() { return (int)history.size(); }

    void rollback(int snap) {
        while ((int)history.size() > snap) {
            Op last = history.back();
            history.pop_back();
            if (last.v != -1) {
                sz[last.u] = last.prev_sz_u;
                parent[last.v] = last.v;
                components++;
            }
            max_comp_size = last.prev_max_comp;
        }
    }
};



struct SegTree {
    int q_count;
    vector<vector<pair<int, int>>> tree;
    SegTree(int q) : q_count(q), tree(4 * q + 5) {}

    void add_edge(int node, int nl, int nr, int l, int r, pair<int, int> edge) {
        if (l >= nr || r <= nl) return;
        if (l <= nl && nr <= r) {
            tree[node].push_back(edge);
            return;
        }
        int mid = (nl + nr) >> 1;
        add_edge(node << 1, nl, mid, l, r, edge);
        add_edge(node << 1 | 1, mid, nr, l, r, edge);
    }
};



struct Query {
    int type, u, v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<Query> queries(q);
    unordered_map<long long, vector<int>> edge_start_times;
    SegTree st(q);

    // 1. Pre-process queries to find the "lifespan" of each edge [start, end)
    for (int i = 0; i < q; ++i) {
        int t; cin >> t;
        if (t == 1) { // Add edge O(log Q.log N)
            int u, v; cin >> u >> v; if (u > v) swap(u, v);
            queries[i] = {t, u, v};
            edge_start_times[((long long)u << 32) | v].push_back(i);
        } else if (t == 2) { // Remove edge O(log Q.log N)
            int u, v; cin >> u >> v; if (u > v) swap(u, v);
            queries[i] = {t, u, v};
            long long key = ((long long)u << 32) | v;
            if (!edge_start_times[key].empty()) {
                int start_idx = edge_start_times[key].back();
                edge_start_times[key].pop_back();
                st.add_edge(1, 0, q, start_idx, i, {u, v});
            }
        } else if (t == 3) { // Is Connected? O(log N)
            int u, v; cin >> u >> v;
            queries[i] = {t, u, v};
        } else if (t == 4) { // Comp Size O(log N)
            int u; cin >> u;
            queries[i] = {t, u, 0};
        } else if (t == 5 || t == 6) { // O(1)
            queries[i] = {t, 0, 0};
        }
    }

    // Edges that were never disconnected last until the end of the query sequence
    for (auto& entry : edge_start_times) {
        long long key = entry.first;
        int u = key >> 32, v = key & 0xFFFFFFFF;
        for (int start_time : entry.second) {
            st.add_edge(1, 0, q, start_time, q, {u, v});
        }
    }

    // 2. DFS through the segment tree to process queries
    DSURollback dsu(n);
    
    function<void(int, int, int)> solve = [&](int node, int nl, int nr) {
        int snap = dsu.snapshot();
        
        // Add all edges that cover this time interval
        for (auto& edge : st.tree[node]) {
            dsu.unite(edge.first, edge.second);
        }

        if (nl + 1 == nr) {
            // Leaf node: answer the query at time index nl
            int type = queries[nl].type;
            if (type == 3) {// Is Connected?
                cout << (dsu.find(queries[nl].u) == dsu.find(queries[nl].v) ? "Yes" : "No") << "\n";
            } else if (type == 4) {//Size of u nodes component
                cout << dsu.sz[dsu.find(queries[nl].u)] << "\n";
            } else if (type == 5) {//Total number of connected components
                cout << dsu.components << "\n";
            } else if (type == 6) {//Size of current largest component 
                cout << dsu.max_comp_size << "\n";
            }
        } else {
            int mid = (nl + nr) >> 1;
            solve(node << 1, nl, mid);
            solve(node << 1 | 1, mid, nr);
        }

        // Rollback DSU to the state before we entered this Segment Tree node
        dsu.rollback(snap);
    };

    if (q > 0) solve(1, 0, q);

    return 0;
}