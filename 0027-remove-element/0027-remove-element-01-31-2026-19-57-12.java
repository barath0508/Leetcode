class Solution {
    public int removeElement(int[] nums, int val) {
        int k = 0; // number of elements not equal to val

        for (int i = 0; i < nums.length; i++) {
            // If current element is not val, keep it
            if (nums[i] != val) {
                nums[k] = nums[i]; // move it to the front region
                k++;               // expand the "valid" region
            }
            // If nums[i] == val, we just skip it (do not increment k)
        }

        // First k elements of nums are now all != val
        return k;
    }
}
