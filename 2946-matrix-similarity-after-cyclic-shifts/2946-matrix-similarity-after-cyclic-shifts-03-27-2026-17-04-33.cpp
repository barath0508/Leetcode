class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        int shift = k % n;  // effective shift

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                int fromCol;
                if (r % 2 == 0) {
                    // even row: left shift
                    fromCol = (c + shift) % n;
                } else {
                    // odd row: right shift
                    fromCol = (c - shift + n) % n;
                }
                if (mat[r][c] != mat[r][fromCol]) {
                    return false;
                }
            }
        }
        return true;
    }
};
