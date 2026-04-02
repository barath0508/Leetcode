class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();
        const long long NEG_INF = (long long)-4e18;

        // dp[i][j][k] = max coins at (i,j) having used k neutralizations (0..2)
        vector<vector<array<long long, 3>>> dp(
            m, vector<array<long long, 3>>(n, {NEG_INF, NEG_INF, NEG_INF})
        );

        int val = coins[0][0];
        if (val >= 0) {
            dp[0][0][0] = val;
        } else {
            dp[0][0][0] = val;   // take the hit
            dp[0][0][1] = 0;     // neutralize here
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                int v = coins[i][j];

                for (int k = 0; k < 3; ++k) {
                    long long best = NEG_INF;

                    // from top
                    if (i > 0 && dp[i-1][j][k] != NEG_INF) {
                        // no neutralization here
                        best = max(best, dp[i-1][j][k] + v);
                    }
                    // from left
                    if (j > 0 && dp[i][j-1][k] != NEG_INF) {
                        best = max(best, dp[i][j-1][k] + v);
                    }

                    // neutralize if v < 0 and we have room to increase k
                    if (v < 0 && k > 0) {
                        // use one neutralization at (i,j), so we must come with k-1
                        if (i > 0 && dp[i-1][j][k-1] != NEG_INF) {
                            best = max(best, dp[i-1][j][k-1]); // add 0 instead of v
                        }
                        if (j > 0 && dp[i][j-1][k-1] != NEG_INF) {
                            best = max(best, dp[i][j-1][k-1]);
                        }
                    }

                    dp[i][j][k] = max(dp[i][j][k], best);
                }
            }
        }

        long long ans = max({dp[m-1][n-1][0], dp[m-1][n-1][1], dp[m-1][n-1][2]});
        return (int)ans;
    }
};