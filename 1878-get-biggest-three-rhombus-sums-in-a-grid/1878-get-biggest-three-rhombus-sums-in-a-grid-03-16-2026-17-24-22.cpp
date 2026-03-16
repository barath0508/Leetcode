#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // 1-based diagonal prefix sums
        // diagDR: up-left -> down-right  (like '\')
        // diagDL: up-right -> down-left  (like '/')
        vector<vector<long long>> diagDR(m + 1, vector<long long>(n + 2, 0));
        vector<vector<long long>> diagDL(m + 1, vector<long long>(n + 2, 0));

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                long long val = grid[i - 1][j - 1];
                diagDR[i][j] = diagDR[i - 1][j - 1] + val;
                diagDL[i][j] = diagDL[i - 1][j + 1] + val;
            }
        }

        // keep largest 3 distinct sums
        set<long long> best;

        auto insertSum = [&](long long s) {
            best.insert(s);
            if (best.size() > 3) best.erase(best.begin()); // drop smallest
        };

        // iterate over all centers (1-based indices for prefix, 0-based for grid)
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // radius 0 rhombus (single cell)
                insertSum(grid[i - 1][j - 1]);

                int maxR = min({i - 1, m - i, j - 1, n - j}); // stay inside grid
                for (int r = 1; r <= maxR; ++r) {
                    // corners in prefix coordinates
                    int top_i = i - r, top_j = j;
                    int right_i = i, right_j = j + r;
                    int bottom_i = i + r, bottom_j = j;
                    int left_i = i, left_j = j - r;

                    // four edges using diagonal prefix sums
                    // top -> right edge (down-right, diagDR)
                    long long TR = diagDR[right_i][right_j] - diagDR[top_i - 1][top_j - 1];

                    // left -> bottom edge (down-right, diagDR)
                    long long LB = diagDR[bottom_i][bottom_j] - diagDR[left_i - 1][left_j - 1];

                    // right -> bottom edge (down-left, diagDL)
                    long long RB = diagDL[bottom_i][bottom_j] - diagDL[right_i - 1][right_j + 1];

                    // top -> left edge (down-left, diagDL)
                    long long TL = diagDL[left_i][left_j] - diagDL[top_i - 1][top_j + 1];

                    long long sum = TR + LB + RB + TL;

                    // subtract 4 corners (each counted twice)
                    sum -= grid[top_i - 1][top_j - 1];
                    sum -= grid[right_i - 1][right_j - 1];
                    sum -= grid[bottom_i - 1][bottom_j - 1];
                    sum -= grid[left_i - 1][left_j - 1];

                    insertSum(sum);
                }
            }
        }

        // output in descending order
        vector<int> ans;
        for (auto it = best.rbegin(); it != best.rend(); ++it)
            ans.push_back((int)*it);
        return ans;
    }
};
