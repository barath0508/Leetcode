class Solution {
    public boolean canPartitionGrid(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        long total = 0L;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                total += grid[i][j];
            }
        }

        if ((total & 1L) == 1L) return false;  // total is odd

        long target = total / 2L;

        // Check horizontal cuts
        long cur = 0L;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cur += grid[i][j];
            }
            if (i < m - 1 && cur == target) {
                return true;
            }
        }

        // Check vertical cuts
        long[] colSum = new long[n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                colSum[j] += grid[i][j];
            }
        }

        cur = 0L;
        for (int j = 0; j < n; j++) {
            cur += colSum[j];
            if (j < n - 1 && cur == target) {
                return true;
            }
        }

        return false;
    }
}