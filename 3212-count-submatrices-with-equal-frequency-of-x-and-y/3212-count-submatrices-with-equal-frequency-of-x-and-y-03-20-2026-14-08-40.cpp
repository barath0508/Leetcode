class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // ps: prefix sum of mapped values (X=1, Y=-1, .=0)
        // px: prefix sum of count of Xs
        vector<vector<int>> ps(n, vector<int>(m, 0));
        vector<vector<int>> px(n, vector<int>(m, 0));

        auto val = [](char c) {
            if (c == 'X') return 1;
            if (c == 'Y') return -1;
            return 0;
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int addVal = val(grid[i][j]);
                int addX   = (grid[i][j] == 'X');

                ps[i][j] = addVal;
                px[i][j] = addX;

                if (i > 0) {
                    ps[i][j] += ps[i - 1][j];
                    px[i][j] += px[i - 1][j];
                }
                if (j > 0) {
                    ps[i][j] += ps[i][j - 1];
                    px[i][j] += px[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    ps[i][j] -= ps[i - 1][j - 1];
                    px[i][j] -= px[i - 1][j - 1];
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int sum = ps[i][j];  // sum of [0..i][0..j]
                int cx  = px[i][j];  // count X in [0..i][0..j]
                if (sum == 0 && cx > 0) {
                    ++ans;
                }
            }
        }

        return (int)ans;
    }
};
