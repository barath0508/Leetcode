class Solution {
public:
    int bitwiseComplement(int n) {
        // Edge case: complement of 0 is 1
        if (n == 0) return 1;

        int mask = 0;
        int temp = n;

        // Build mask with all bits = 1 for the length of n
        while (temp > 0) {
            mask = (mask << 1) | 1;
            temp >>= 1;
        }

        // XOR with mask flips all bits within that length
        return n ^ mask;
    }
};
