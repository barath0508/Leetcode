class Solution {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        int i = m - 1;          // last valid index in nums1
        int j = n - 1;          // last index in nums2
        int k = m + n - 1;      // last index in nums1 (total length)

        // merge from the back
        while (j >= 0) {        // until nums2 is exhausted
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }
    }
}
