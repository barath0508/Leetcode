class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        // primes of possible bit counts up to 20
        const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
        bool isPrime[21] = {false};
        for (int p : primes) isPrime[p] = true;

        int ans = 0;
        for (int x = left; x <= right; ++x) {
            int cnt = __builtin_popcount(x);  // number of set bits
            if (isPrime[cnt]) {
                ++ans;
            }
        }
        return ans;
    }
};
