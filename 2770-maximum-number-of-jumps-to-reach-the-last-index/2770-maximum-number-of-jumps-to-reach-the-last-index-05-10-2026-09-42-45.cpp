class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        const int NEG_INF = -1000000007; // a large negative sentinel

        vector<int> dp(n, NEG_INF);
        dp[0] = 0; // starting at index 0 requires 0 jumps

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] == NEG_INF) continue; // cannot reach j
                long long diff = (long long)nums[i] - nums[j];
                if (diff >= - (long long)target && diff <= (long long)target) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n - 1] < 0 ? -1 : dp[n - 1];
    }
};