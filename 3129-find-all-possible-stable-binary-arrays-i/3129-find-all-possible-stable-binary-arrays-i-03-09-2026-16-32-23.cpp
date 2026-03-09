class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        const int MOD = 1'000'000'007;

        // dp0[z][o][len], dp1[z][o][len]
        // Use 4D vectors or flatten; here we use 3D for each.
        static int dp0[201][201][201];
        static int dp1[201][201][201];

        // Initialize to 0
        for (int z = 0; z <= zero; ++z)
            for (int o = 0; o <= one; ++o)
                for (int l = 0; l <= limit; ++l)
                    dp0[z][o][l] = dp1[z][o][l] = 0;

        // base: one element
        if (zero >= 1) dp0[1][0][1] = 1;
        if (one  >= 1) dp1[0][1][1] = 1;

        for (int z = 0; z <= zero; ++z) {
            for (int o = 0; o <= one; ++o) {
                for (int len = 1; len <= limit; ++len) {
                    int cur0 = dp0[z][o][len];
                    int cur1 = dp1[z][o][len];

                    if (cur0) {
                        // extend 0 run
                        if (z + 1 <= zero && len + 1 <= limit) {
                            dp0[z + 1][o][len + 1] =
                                (dp0[z + 1][o][len + 1] + cur0) % MOD;
                        }
                        // switch to 1
                        if (o + 1 <= one) {
                            dp1[z][o + 1][1] =
                                (dp1[z][o + 1][1] + cur0) % MOD;
                        }
                    }

                    if (cur1) {
                        // extend 1 run
                        if (o + 1 <= one && len + 1 <= limit) {
                            dp1[z][o + 1][len + 1] =
                                (dp1[z][o + 1][len + 1] + cur1) % MOD;
                        }
                        // switch to 0
                        if (z + 1 <= zero) {
                            dp0[z + 1][o][1] =
                                (dp0[z + 1][o][1] + cur1) % MOD;
                        }
                    }
                }
            }
        }

        long long ans = 0;
        for (int len = 1; len <= limit; ++len) {
            ans = (ans + dp0[zero][one][len]) % MOD;
            ans = (ans + dp1[zero][one][len]) % MOD;
        }
        return (int)ans;
    }
};
