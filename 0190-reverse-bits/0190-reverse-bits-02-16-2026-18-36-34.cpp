class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for (int i = 0; i < 32; i++) {
            res <<= 1;          // make room for next bit
            res |= (n & 1);     // put current LSB of n into res
            n >>= 1;            // move to next bit of n
        }
        return res;
    }
};
