class Solution {
    public int[][] constructProductMatrix(int[][] grid) {
        final int MOD = 12345;
        int n = grid.length;
        int m = grid[0].length;

        int[][] ans = new int[n][m];

        // 1) Backward pass: store suffix products
        long suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                ans[i][j] = (int) suffix;                   // product of all elements after (i, j)
                suffix = (suffix * grid[i][j]) % MOD;       // extend suffix with current element
            }
        }

        // 2) Forward pass: combine with prefix products
        long prefix = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans[i][j] = (int) ((ans[i][j] * prefix) % MOD);  // prefix * suffix (excluding grid[i][j])
                prefix = (prefix * grid[i][j]) % MOD;            // extend prefix with current element
            }
        }

        return ans;
    }
}
