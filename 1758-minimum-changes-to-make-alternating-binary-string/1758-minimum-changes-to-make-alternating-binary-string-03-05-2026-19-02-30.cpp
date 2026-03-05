class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int cnt0 = 0; // mismatch count if pattern is "0101..."
        int cnt1 = 0; // mismatch count if pattern is "1010..."

        for (int i = 0; i < n; ++i) {
            char expected0 = (i % 2 == 0) ? '0' : '1'; // for "0101..."
            char expected1 = (i % 2 == 0) ? '1' : '0'; // for "1010..."

            if (s[i] != expected0) cnt0++;
            if (s[i] != expected1) cnt1++;
        }

        return min(cnt0, cnt1);
    }
};
