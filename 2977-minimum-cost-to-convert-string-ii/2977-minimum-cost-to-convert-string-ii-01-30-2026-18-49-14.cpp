class Solution {
public:
    long long minimumCost(string source, string target,
                          vector<string>& original,
                          vector<string>& changed,
                          vector<int>& cost) {
        const long long INF = (long long)4e18;
        int k = cost.size();

        // 1) Compress pattern strings
        unordered_map<string,int> id;
        vector<string> patterns;
        auto getId = [&](const string& s) -> int {
            auto it = id.find(s);
            if (it != id.end()) return it->second;
            int nid = patterns.size();
            id[s] = nid;
            patterns.push_back(s);
            return nid;
        };

        for (int i = 0; i < k; ++i) {
            getId(original[i]);
            getId(changed[i]);
        }
        int m = patterns.size();

        // 2) Build graph and run Floyd–Warshall
        vector<vector<long long>> g(m, vector<long long>(m, INF));
        for (int i = 0; i < m; ++i) g[i][i] = 0;
        for (int i = 0; i < k; ++i) {
            int u = id[original[i]];
            int v = id[changed[i]];
            g[u][v] = min(g[u][v], (long long)cost[i]);
        }

        for (int x = 0; x < m; ++x)
            for (int i = 0; i < m; ++i)
                if (g[i][x] < INF)
                    for (int j = 0; j < m; ++j)
                        if (g[x][j] < INF)
                            g[i][j] = min(g[i][j], g[i][x] + g[x][j]);

        int n = source.size();

        // 3) Precompute matches
        vector<vector<pair<int,int>>> srcMatch(n), tgtMatch(n);
        for (int pid = 0; pid < m; ++pid) {
            const string& p = patterns[pid];
            int L = p.size();
            if (L > n) continue;

            // matches in source
            for (int i = 0; i + L <= n; ++i)
                if (source.compare(i, L, p) == 0)
                    srcMatch[i].push_back({L, pid});

            // matches in target
            for (int i = 0; i + L <= n; ++i)
                if (target.compare(i, L, p) == 0)
                    tgtMatch[i].push_back({L, pid});
        }

        // 4) DP over positions
        vector<long long> dp(n + 1, INF);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i) {
            // no-op if chars equal
            if (source[i] == target[i])
                dp[i] = min(dp[i], dp[i + 1]);

            // substring conversions
            for (auto [len1, u] : srcMatch[i]) {
                for (auto [len2, v] : tgtMatch[i]) {
                    if (len1 != len2) continue;
                    long long cv = g[u][v];
                    if (cv >= INF) continue;
                    int j = i + len1;
                    if (j <= n && dp[j] < INF)
                        dp[i] = min(dp[i], cv + dp[j]);
                }
            }
        }

        return dp[0] >= INF ? -1 : dp[0];
    }
};
