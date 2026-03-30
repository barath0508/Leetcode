class Solution {
public:
    bool checkStrings(string s1, string s2) {
        int n = s1.size();
        
        // 26 letters for even and odd positions
        int even1[26] = {0}, even2[26] = {0};
        int odd1[26]  = {0}, odd2[26]  = {0};
        
        for (int i = 0; i < n; ++i) {
            int c1 = s1[i] - 'a';
            int c2 = s2[i] - 'a';
            if (i % 2 == 0) {
                even1[c1]++;
                even2[c2]++;
            } else {
                odd1[c1]++;
                odd2[c2]++;
            }
        }
        
        for (int k = 0; k < 26; ++k) {
            if (even1[k] != even2[k]) return false;
            if (odd1[k]  != odd2[k])  return false;
        }
        
        return true;
    }
};