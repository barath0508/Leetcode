class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> tail(n, 0);

        // 1. Count trailing zeros for each row
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 0) cnt++;
                else break;
            }
            tail[i] = cnt;
        }

        int ans = 0;

        // 2. Place rows from top to bottom
        for (int i = 0; i < n; ++i) {
            int need = n - 1 - i;        // required trailing zeros for row i

            int j = i;
            while (j < n && tail[j] < need) {
                j++;
            }

            if (j == n) return -1;       // cannot find a valid row

            // 3. Bring row j up to i using adjacent swaps
            ans += (j - i);
            while (j > i) {
                swap(tail[j], tail[j - 1]);
                j--;
            }
        }

        return ans;
    }
};
