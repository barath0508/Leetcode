class Solution {
    public int minimumCost(int[] nums) {
        int n = nums.length;
        
        // First subarray always starts at index 0
        int ans = nums[0];

        // Find the two smallest elements in nums[1..n-1]
        int mn1 = Integer.MAX_VALUE;
        int mn2 = Integer.MAX_VALUE;

        for (int i = 1; i < n; i++) {
            int x = nums[i];
            if (x < mn1) {
                mn2 = mn1;
                mn1 = x;
            } else if (x < mn2) {
                mn2 = x;
            }
        }

        return ans + mn1 + mn2;
    }
}
