class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        const int MOD = 1'000'000'007;

        vector<vector<int>> dp0(zero + 1, vector<int>(one + 1));
        vector<vector<int>> dp1(zero + 1, vector<int>(one + 1));
        // pre0[i][j] = sum_{y=0..j} dp0[i][y]
        // pre1[i][j] = sum_{x=0..i} dp1[x][j]
        vector<vector<int>> pre0(zero + 1, vector<int>(one + 1));
        vector<vector<int>> pre1(zero + 1, vector<int>(one + 1));

        for (int i = 0; i <= zero; ++i) {
            for (int j = 0; j <= one; ++j) {
                long long v0 = 0, v1 = 0;

                // end with 0
                if (i > 0) {
                    int l = max(0, i - limit);
                    int r = i - 1;
                    if (r >= 0) {
                        long long sum = pre1[r][j];
                        if (l > 0) sum = (sum - pre1[l - 1][j] + MOD) % MOD;
                        v0 = (v0 + sum) % MOD;
                    }
                    if (j == 0 && i <= limit) v0 = (v0 + 1) % MOD;
                }

                // end with 1
                if (j > 0) {
                    int l = max(0, j - limit);
                    int r = j - 1;
                    if (r >= 0) {
                        long long sum = pre0[i][r];
                        if (l > 0) sum = (sum - pre0[i][l - 1] + MOD) % MOD;
                        v1 = (v1 + sum) % MOD;
                    }
                    if (i == 0 && j <= limit) v1 = (v1 + 1) % MOD;
                }

                dp0[i][j] = (int)v0;
                dp1[i][j] = (int)v1;

                // update prefix sums
                pre0[i][j] = dp0[i][j];
                if (j > 0) {
                    pre0[i][j] += pre0[i][j - 1];
                    if (pre0[i][j] >= MOD) pre0[i][j] -= MOD;
                }
                pre1[i][j] = dp1[i][j];
                if (i > 0) {
                    pre1[i][j] += pre1[i - 1][j];
                    if (pre1[i][j] >= MOD) pre1[i][j] -= MOD;
                }
            }
        }

        return (dp0[zero][one] + dp1[zero][one]) % MOD;
    }
};
