class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        string t = s + s;                  // length 2n

        string alt1, alt2;
        alt1.reserve(2 * n);
        alt2.reserve(2 * n);

        // Build alternating patterns of length 2n
        for (int i = 0; i < 2 * n; ++i) {
            if (i % 2 == 0) {
                alt1.push_back('0');       // 0101...
                alt2.push_back('1');       // 1010...
            } else {
                alt1.push_back('1');
                alt2.push_back('0');
            }
        }

        int mis1 = 0, mis2 = 0;
        int ans = n;

        for (int i = 0; i < 2 * n; ++i) {
            // Include current index i into the window
            if (t[i] != alt1[i]) ++mis1;
            if (t[i] != alt2[i]) ++mis2;

            // If window larger than n, remove leftmost index
            if (i >= n) {
                int left = i - n;
                if (t[left] != alt1[left]) --mis1;
                if (t[left] != alt2[left]) --mis2;
            }

            // When window size == n, update answer
            if (i >= n - 1) {
                ans = min(ans, min(mis1, mis2));
            }
        }

        return ans;
    }
};
