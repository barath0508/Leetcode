class Solution {
    public int minimumDistance(int[] nums) {
        int n = nums.length;

        int[] next = new int[n];
        int[] last = new int[n + 1]; // values are in [1, n]

        // Initialize
        for (int i = 0; i < n; i++) {
            next[i] = -1;
        }
        for (int v = 0; v <= n; v++) {
            last[v] = -1;
        }

        // Build next[] using right-to-left scan
        for (int i = n - 1; i >= 0; i--) {
            int value = nums[i];
            next[i] = last[value]; // next occurrence index or -1
            last[value] = i;
        }

        int ans = Integer.MAX_VALUE;

        // Check triples via i -> next[i] -> next[next[i]]
        for (int i = 0; i < n; i++) {
            int second = next[i];
            if (second == -1) continue;

            int third = next[second];
            if (third == -1) continue;

            ans = Math.min(ans, 2 * (third - i)); // distance = 2 * (k - i)
        }

        return ans == Integer.MAX_VALUE ? -1 : ans;
    }
}