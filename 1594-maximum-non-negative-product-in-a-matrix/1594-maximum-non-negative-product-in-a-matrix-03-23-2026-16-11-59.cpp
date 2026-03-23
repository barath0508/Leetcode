class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        const long long MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        vector<vector<long long>> mx(m, vector<long long>(n));
        vector<vector<long long>> mn(m, vector<long long>(n));

        mx[0][0] = mn[0][0] = grid[0][0];

        for (int j = 1; j < n; ++j) {
            long long val = grid[0][j];
            long long prev = mx[0][j - 1];
            mx[0][j] = mn[0][j] = prev * val;
        }

        for (int i = 1; i < m; ++i) {
            long long val = grid[i][0];
            long long prev = mx[i - 1][0];
            mx[i][0] = mn[i][0] = prev * val;
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                long long val = grid[i][j];

                long long a = mx[i - 1][j] * val;
                long long b = mn[i - 1][j] * val;
                long long c = mx[i][j - 1] * val;
                long long d = mn[i][j - 1] * val;

                mx[i][j] = max(max(a, b), max(c, d));
                mn[i][j] = min(min(a, b), min(c, d));
            }
        }

        long long best = mx[m - 1][n - 1];
        if (best < 0) return -1;
        return (int)(best % MOD);
    }
};
