class Solution {
    public boolean isTrionic(int[] nums) {
        int n = nums.length;

        // Try all possible p, q with 0 < p < q < n-1
        for (int p = 1; p <= n - 3; p++) {
            for (int q = p + 1; q <= n - 2; q++) {

                if (isStrictInc(nums, 0, p) &&
                    isStrictDec(nums, p, q) &&
                    isStrictInc(nums, q, n - 1)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Check nums[l..r] is strictly increasing
    private boolean isStrictInc(int[] nums, int l, int r) {
        for (int i = l; i < r; i++) {
            if (nums[i] >= nums[i + 1]) {
                return false;
            }
        }
        return true;
    }

    // Check nums[l..r] is strictly decreasing
    private boolean isStrictDec(int[] nums, int l, int r) {
        for (int i = l; i < r; i++) {
            if (nums[i] <= nums[i + 1]) {
                return false;
            }
        }
        return true;
    }
}
