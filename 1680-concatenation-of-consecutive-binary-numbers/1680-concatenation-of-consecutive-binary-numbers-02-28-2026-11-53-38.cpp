class Solution {
public:
    int concatenatedBinary(int n) {
        long long result = 0;
        int len = 0;
        const int MOD = 1e9 + 7;
        for (int i = 1; i <= n; i++) {
            // Check if i is a power of 2 (new bit needed)
            if ((i & (i - 1)) == 0) len++;
            result = ((result << len) | i) % MOD;
        }
        return (int)result;
    }
};