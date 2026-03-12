class DSU {
public:
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

class Solution {
public:
    long long maxStability(int n, vector<vector<int>>& edges, int k) {
        // Separate storing so we can sort once
        struct Edge {
            int u, v, s, must;
        };
        int m = edges.size();
        vector<Edge> e(m);
        int maxS = 0;
        for (int i = 0; i < m; i++) {
            e[i] = {edges[i][0], edges[i][1], edges[i][2], edges[i][3]};
            maxS = max(maxS, edges[i][2]);
        }

        // Sort by strength descending
        sort(e.begin(), e.end(), [](const Edge& a, const Edge& b) {
            return a.s > b.s;
        });

        auto can = [&](long long X) -> bool {
            DSU dsu(n);
            int cntEdges = 0;
            long long usedUpgrades = 0;

            // First, mandatory edges
            for (const auto& ed : e) {
                if (ed.must == 1) {
                    // Can't upgrade; if too weak for X, impossible
                    if (ed.s < X) return false;
                    // Must be included, but without forming a cycle
                    if (!dsu.unite(ed.u, ed.v)) {
                        // Cycle among mandatory edges -> impossible
                        return false;
                    }
                    cntEdges++;
                }
            }

            // Now, optional edges
            for (const auto& ed : e) {
                if (ed.must == 1) continue; // already processed
                if (cntEdges == n - 1) break;
                int u = ed.u, v = ed.v;
                if (dsu.find(u) == dsu.find(v)) continue; // skip cycles

                if (ed.s >= X) {
                    // Good enough without upgrade
                    dsu.unite(u, v);
                    cntEdges++;
                } else if ((long long)ed.s * 2 >= X) {
                    // Can reach X only with upgrade
                    if (usedUpgrades < k) {
                        usedUpgrades++;
                        dsu.unite(u, v);
                        cntEdges++;
                    }
                }
                // else: can't help for stability X
            }

            return (cntEdges == n - 1);
        };

        long long lo = 1, hi = (long long)maxS * 2, ans = -1;
        while (lo <= hi) {
            long long mid = (lo + hi) / 2;
            if (can(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};
