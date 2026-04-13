class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int n = nums.size();
        int ans = n; // max possible distance is <= n-1

        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                int dist = abs(i - start);
                if (dist < ans) {
                    ans = dist;
                }
            }
        }

        return ans;
    }
};