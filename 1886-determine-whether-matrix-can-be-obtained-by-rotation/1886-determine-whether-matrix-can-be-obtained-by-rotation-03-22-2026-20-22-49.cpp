class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        
        auto equalMatrix = [&](const vector<vector<int>>& A,
                               const vector<vector<int>>& B) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (A[i][j] != B[i][j]) return false;
                }
            }
            return true;
        };
        
        auto rotate90 = [&](vector<vector<int>>& A) {
            // transpose
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    swap(A[i][j], A[j][i]);
                }
            }
            // reverse each row
            for (int i = 0; i < n; ++i) {
                reverse(A[i].begin(), A[i].end());
            }
        };
        
        // Try 0°, 90°, 180°, 270°
        for (int k = 0; k < 4; ++k) {
            if (equalMatrix(mat, target)) return true;
            rotate90(mat);
        }
        
        return false;
    }
};
