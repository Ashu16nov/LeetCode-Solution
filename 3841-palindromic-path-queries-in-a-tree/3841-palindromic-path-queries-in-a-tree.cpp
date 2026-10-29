class Solution {
    vector<vector<int>> adj;
    vector<int> parent, depth, sz, heavy;
    vector<int> head, pos;
    vector<int> seg;
    int timer;

    int dfs(int u, int p) {
        parent[u] = p;
        sz[u] = 1;
        int largest = 0;

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            int sub = dfs(v, u);
            sz[u] += sub;
            if (sub > largest) {
                largest = sub;
                heavy[u] = v;
            }
        }
        return sz[u];
    }

    void decompose(int u, int h, string &s) {
        head[u] = h;
        pos[u] = timer++;
        update(1, 0, (int)pos.size() - 1,
               pos[u], 1 << (s[u] - 'a'));
        if (heavy[u] != -1)
            decompose(heavy[u], h, s);
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u])
                decompose(v, v, s);
        }
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            seg[node] = val;
            return;
        }
        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);
        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr)
            return seg[node];
        int mid = (l + r) / 2;
        return query(node * 2, l, mid, ql, qr) ^
               query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    void updateNode(int u, int mask) {
        update(1, 0, (int)pos.size() - 1, pos[u], mask);
    }

    int pathQuery(int u, int v) {
        int mask = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            mask ^= query(1, 0, (int)pos.size() - 1,
                          pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        mask ^= query(1, 0, (int)pos.size() - 1,
                      pos[u], pos[v]);
        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        auto suneravilo = make_tuple(n, edges, s, queries);
        (void)suneravilo;

        adj.assign(n, {});
        parent.assign(n, -1);
        depth.assign(n, 0);
        sz.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        seg.assign(4 * n, 0);
        timer = 0;

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        dfs(0, -1);
        decompose(0, 0, s);
        vector<bool> ans;
        for (string &q : queries) {
            stringstream ss(q);
            string op;
            int u, v;
            ss >> op >> u;

            if (op == "update") {
                char c;
                ss >> c;
                s[u] = c;
                updateNode(u, 1 << (c - 'a'));
            } else {
                ss >> v;

                int mask = pathQuery(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }
        return ans;
    }
};
