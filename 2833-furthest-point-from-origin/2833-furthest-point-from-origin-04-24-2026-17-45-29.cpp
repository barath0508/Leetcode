class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int cntL = 0, cntR = 0, cntU = 0;
        for (char c : moves) {
            if (c == 'L') cntL++;
            else if (c == 'R') cntR++;
            else cntU++;  // '_'
        }

        // Scenario 1: all '_' -> 'L'
        int totalL1 = cntL + cntU;
        int totalR1 = cntR;
        int final1 = totalR1 - totalL1;  // R is +1, L is -1

        // Scenario 2: all '_' -> 'R'
        int totalL2 = cntL;
        int totalR2 = cntR + cntU;
        int final2 = totalR2 - totalL2;

        return max(abs(final1), abs(final2));
    }
};