class Solution {
public:
    int countBinarySubstrings(string s) {
        int n = s.size();
        if (n <= 1) return 0;

        int prev_run = 0;    // length of previous group of same chars
        int curr_run = 1;    // length of current group, starting at s[0]
        int ans = 0;

        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i - 1]) {
                // still in the same run
                curr_run++;
            } else {
                // run ended; count substrings between prev and curr run
                ans += min(prev_run, curr_run);
                // shift current run to previous
                prev_run = curr_run;
                // new run starts
                curr_run = 1;
            }
        }

        // account for the last run with its previous one
        ans += min(prev_run, curr_run);
        return ans;
    }
};
