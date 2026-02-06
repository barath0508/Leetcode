class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int left = 0;
        int maxLen = 1; // at least one element

        for (int right = 0; right < n; ++right) {
            // shrink window until it becomes balanced
            while (left <= right && (long long)nums[right] > 1LL * k * nums[left]) {
                ++left;
            }
            // now [left, right] is balanced
            maxLen = max(maxLen, right - left + 1);
        }

        return n - maxLen;
    }
};
