class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size();

        // Count initial zeros
        int z0 = 0;
        for (char c : s) if (c == '0') z0++;

        // Already all ones
        if (z0 == 0) return 0;

        // Distance (BFS levels) on states 0..n
        vector<int> dist(n + 1, -1);
        queue<int> q;

        // Unvisited states, split by parity
        std::set<int> unvisited[2];
        for (int z = 0; z <= n; ++z) {
            if (z == z0) continue;
            unvisited[z & 1].insert(z);
        }

        // Start BFS from initial zero-count
        dist[z0] = 0;
        q.push(z0);

        while (!q.empty()) {
            int z = q.front();
            q.pop();

            if (z == 0) return dist[z];

            int L = max(0, k - (n - z));
            int R = min(k, z);
            if (L > R) continue;

            int z_min = z + k - 2 * R;
            int z_max = z + k - 2 * L;

            int p = (z + k) & 1; // parity of reachable states

            auto &st = unvisited[p];
            auto it = st.lower_bound(z_min);
            while (it != st.end() && *it <= z_max) {
                int nz = *it;
                dist[nz] = dist[z] + 1;
                q.push(nz);

                auto to_erase = it;
                ++it;
                st.erase(to_erase);
            }
        }

        return -1;
    }
};
