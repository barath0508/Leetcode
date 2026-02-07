class Solution {
public:
    int minimumDeletions(string s) {
        int bCount = 0;   // number of 'b's seen so far
        int res = 0;      // minimum deletions so far
        
        for (char c : s) {
            if (c == 'b') {
                bCount++;  // keep this 'b' for now
            } else { // c == 'a'
                // Option 1: delete this 'a'  -> res + 1
                // Option 2: delete all previous 'b's -> bCount
                res = min(res + 1, bCount);
            }
        }
        
        return res;
    }
};
