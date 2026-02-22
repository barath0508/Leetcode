class Solution {
public:
    int binaryGap(int n) {
        int lastOnePos = -1;      // position of previous 1 bit
        int maxGap = 0;           // answer
        int index = 0;            // current bit position

        while (n > 0) {
            if (n & 1) {          // if current bit is 1
                if (lastOnePos != -1) {
                    int gap = index - lastOnePos;
                    if (gap > maxGap) {
                        maxGap = gap;
                    }
                }
                lastOnePos = index;
            }
            n >>= 1;              // move to next bit
            index++;
        }

        return maxGap;
    }
};
