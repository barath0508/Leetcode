class Solution {
    // Convert letter 'A'..'Z' to 0..25
    private int idx(char c) {
        return c - 'A';
    }

    // Manhattan distance on 6x5 keyboard
    private int dist(char a, char b) {
        int ia = idx(a), ib = idx(b);
        int ra = ia / 6, ca = ia % 6;
        int rb = ib / 6, cb = ib % 6;
        return Math.abs(ra - rb) + Math.abs(ca - cb);
    }

    private String word;
    private int n;
    private Integer[][] memo; // memo[i][j+1], j = -1..i

    public int minimumDistance(String word) {
        this.word = word;
        this.n = word.length();
        // i ranges 0..n-1, j ranges -1..n-1 -> shift j by +1 to store in 0..n
        memo = new Integer[n][n + 1];
        // First character typed by some finger for free; other finger not used yet (j = -1)
        return dfs(0, -1);
    }

    // After typing word[i], other finger is at word[j] (or j == -1 if unused)
    private int dfs(int i, int j) {
        if (i == n - 1) return 0;          // already at last character
        if (memo[i][j + 1] != null) return memo[i][j + 1];

        char curr = word.charAt(i);
        char next = word.charAt(i + 1);

        // Option 1: same finger (on curr) types next
        int costSame = dist(curr, next) + dfs(i + 1, j);

        // Option 2: other finger (on j) types next
        int moveOther = 0;
        if (j != -1) {
            moveOther = dist(word.charAt(j), next);
        } // else 0, since initial position is free
        int costOther = moveOther + dfs(i + 1, i);

        int ans = Math.min(costSame, costOther);
        memo[i][j + 1] = ans;
        return ans;
    }
}