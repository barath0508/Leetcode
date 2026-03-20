class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int outRows = m - k + 1;
        int outCols = n - k + 1;

        vector<vector<int>> ans(outRows, vector<int>(outCols));

        for (int i = 0; i <= m - k; ++i) {
            for (int j = 0; j <= n - k; ++j) {
                vector<int> vals;
                vals.reserve(k * k);

                for (int r = i; r < i + k; ++r) {
                    for (int c = j; c < j + k; ++c) {
                        vals.push_back(grid[r][c]);
                    }
                }

                sort(vals.begin(), vals.end());

                int best = INT_MAX;
                for (int t = 0; t + 1 < (int)vals.size(); ++t) {
                    int diff = vals[t + 1] - vals[t];
                    if (diff == 0) continue;           // ignore same values
                    best = min(best, diff);
                }
                if (best == INT_MAX) best = 0;         // all values same

                ans[i][j] = best;
            }
        }
        return ans;
    }
};
