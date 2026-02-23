class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        if (n < k) return false;

        int total = 1 << k;            // 2^k
        if (n - k + 1 < total) return false;

        vector<bool> seen(total, false);
        int mask = total - 1;
        int val = 0;

        // Build initial window of size k
        for (int i = 0; i < k; ++i) {
            val = (val << 1) | (s[i] - '0');
        }
        if (!seen[val]) {
            seen[val] = true;
            --total;
        }

        // Slide window over the rest of the string
        for (int i = k; i < n && total > 0; ++i) {
            val = ((val << 1) & mask) | (s[i] - '0');
            if (!seen[val]) {
                seen[val] = true;
                --total;
            }
        }

        return total == 0;
    }
};
