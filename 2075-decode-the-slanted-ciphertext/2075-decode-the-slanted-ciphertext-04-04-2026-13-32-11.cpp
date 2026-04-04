class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        int n = encodedText.size();
        if (n == 0) return "";

        int cols = n / rows;          // number of columns in the matrix
        string result;
        result.reserve(n);

        // For each diagonal starting in the first row
        for (int startCol = 0; startCol < cols; ++startCol) {
            int r = 0, c = startCol;
            while (r < rows && c < cols) {
                int idx = r * cols + c;   // 2D -> 1D index
                result.push_back(encodedText[idx]);
                ++r;
                ++c;                      // move down-right
            }
        }

        // Remove trailing spaces
        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }

        return result;
    }
};