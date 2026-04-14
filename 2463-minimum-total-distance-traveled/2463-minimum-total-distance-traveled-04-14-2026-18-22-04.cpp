class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });

        // Expand factories into slots
        vector<long long> slots;
        for (auto &f : factory) {
            long long pos = f[0];
            int limit = f[1];
            for (int c = 0; c < limit; ++c) {
                slots.push_back(pos);
            }
        }

        int m = robot.size();
        int k = slots.size();
        const long long INF = (long long)4e18;

        // dp[i][j] = min cost for robots[i..] using slots[j..]
        vector<vector<long long>> dp(m + 1, vector<long long>(k + 1, 0));

        // Base: dp[m][j] = 0 for all j (no robots left)
        for (int j = 0; j <= k; ++j) dp[m][j] = 0;

        // Fill from bottom-right to top-left
        for (int i = m - 1; i >= 0; --i) {
            dp[i][k] = INF; // no slots left but robots remain
            for (int j = k - 1; j >= 0; --j) {
                long long take = llabs((long long)robot[i] - slots[j]) + dp[i + 1][j + 1];
                long long skip = dp[i][j + 1];
                dp[i][j] = min(take, skip);
            }
        }

        return dp[0][0];
    }
};