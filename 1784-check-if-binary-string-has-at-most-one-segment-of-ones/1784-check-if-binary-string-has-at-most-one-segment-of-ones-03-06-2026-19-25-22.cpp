class Solution {
public:
    bool checkOnesSegment(string s) {
        int n = s.size();
        for (int i = 0; i + 1 < n; ++i) {
            if (s[i] == '0' && s[i + 1] == '1') {
                // Found a new '1' segment after a '0'
                return false;
            }
        }
        return true;
    }
};
