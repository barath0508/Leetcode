class Solution {
public:
    char invert(char c) {
        return (c == '0') ? '1' : '0';
    }
    
    char solve(int n, long long k) {
        if (n == 1) return '0';              // S1 = "0"
        
        long long len = (1LL << n) - 1;      // length of Sn = 2^n - 1
        long long mid = (len + 1) / 2;       // mid = 2^(n-1)
        
        if (k == mid) {
            return '1';                      // middle bit of Sn
        } else if (k < mid) {
            return solve(n - 1, k);          // in left part Sn-1
        } else {                             // in right part
            long long idx = len - k + 1;     // mirror index in Sn-1
            char b = solve(n - 1, idx);      // corresponding bit in Sn-1
            return invert(b);                // because of invert()
        }
    }
    
    char findKthBit(int n, int k) {
        return solve(n, k);
    }
};
