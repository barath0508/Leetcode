class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string s(n, 0);

        // Basic necessary checks: diagonal and symmetry
        for (int i = 0; i < n; ++i) {
            if (lcp[i][i] != n - i) return "";
            for (int j = 0; j < n; ++j) {
                if (lcp[i][j] != lcp[j][i]) return "";
            }
        }

        char cur = 'a' - 1;

        // Step 1: greedy construction
        for (int i = 0; i < n; ++i) {
            if (s[i] != 0) continue;
            if (++cur > 'z') return ""; // more groups than 26 letters
            s[i] = cur;

            for (int j = i + 1; j < n; ++j) {
                if (lcp[i][j] > 0) {
                    if (s[j] != 0 && s[j] != cur) return "";
                    s[j] = cur;
                }
            }
        }

        // All must be assigned
        for (char c : s)
            if (c == 0) return "";

        // Step 2: validate lcp with recurrence
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (s[i] == s[j]) {
                    if (i == n - 1 || j == n - 1) {
                        if (lcp[i][j] != 1) return "";
                    } else {
                        if (lcp[i][j] != lcp[i + 1][j + 1] + 1) return "";
                    }
                } else {
                    if (lcp[i][j] != 0) return "";
                }
            }
        }

        return s;
    }
};