class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            int cnt[26] = {0};

            for (int j = i; j < n; ++j) {
                cnt[s[j] - 'a']++;

                int base = 0;
                bool ok = true;

                for (int c = 0; c < 26; ++c) {
                    if (cnt[c] == 0) continue;
                    if (base == 0) base = cnt[c];
                    else if (cnt[c] != base) {
                        ok = false;
                        break;
                    }
                }

                if (ok) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};
