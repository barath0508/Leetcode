class Solution {
public:
    int longestBalanced(string s) {
        int ans = 0;
        ans = max(ans, case1(s));
        ans = max(ans, case2(s));
        ans = max(ans, case3(s));
        return ans;
    }

private:
    // Case 1: only one character
    int case1(const string &s){
        int n = s.size();
        int best = 0, i = 0;
        while (i < n){
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            best = max(best, j - i);
            i = j;
        }
        return best;
    }

    // Case 2: exactly two distinct characters
    int case2_pair(const string &s, char x, char y){
        int n = s.size();
        unordered_map<int,int> firstPos;
        int bal = 0;
        int best = 0;

        firstPos[0] = 0;      // balance 0 before the string
        int last_bad = -1;    // last index of the third character

        for (int i = 0; i < n; ++i){
            char c = s[i];
            if (c == x) {
                bal += 1;
            } else if (c == y) {
                bal -= 1;
            } else {
                // third character: reset segment
                bal = 0;
                firstPos.clear();
                firstPos[0] = i + 1;
                last_bad = i;
                continue;
            }

            int idx = i + 1;          // prefix index
            if (!firstPos.count(bal)) firstPos[bal] = idx;

            int start = firstPos[bal];
            int len = idx - start;

            // len >= 2 ensures at least two chars in substring.
            // With balance equal and only x,y present, both must appear.
            if (len >= 2) best = max(best, len);
        }
        return best;
    }

    int case2(const string &s){
        int ans = 0;
        ans = max(ans, case2_pair(s, 'a', 'b'));
        ans = max(ans, case2_pair(s, 'a', 'c'));
        ans = max(ans, case2_pair(s, 'b', 'c'));
        return ans;
    }

    // pack pair (dx, dy) into 64-bit key
    long long pack(long long x, long long y){
        return (x << 32) ^ (y & 0xffffffff);
    }

    // Case 3: all three characters
    int case3(const string &s){
        int n = s.size();
        long long A = 0, B = 0, C = 0;
        unordered_map<long long,int> firstPos;
        long long key0 = pack(0, 0);
        firstPos[key0] = 0;
        int best = 0;

        for (int i = 0; i < n; ++i){
            if (s[i] == 'a') A++;
            else if (s[i] == 'b') B++;
            else C++;

            long long dx = B - A;
            long long dy = C - A;
            long long key = pack(dx, dy);

            if (!firstPos.count(key)){
                firstPos[key] = i + 1;
            } else {
                int len = (i + 1) - firstPos[key];
                best = max(best, len);
            }
        }
        return best;
    }
};
