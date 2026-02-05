class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);

        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            if (x == 0) {
                result[i] = 0;  // or nums[i]
            } else {
                // safe circular index
                int target = (i + x % n + n) % n;
                result[i] = nums[target];
            }
        }
        return result;
    }
};
