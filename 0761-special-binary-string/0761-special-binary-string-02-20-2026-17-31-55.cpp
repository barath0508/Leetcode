class Solution {
public:
    string makeLargestSpecial(string s) {
        int n = s.size();
        if (n <= 2) return s;   // base: "10" or empty

        vector<string> blocks;
        int balance = 0, start = 0;

        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') balance++;
            else balance--;

            if (balance == 0) {
                // s[start..i] is a primitive special block: 1 + inner + 0
                string inner = s.substr(start + 1, i - start - 1);
                inner = makeLargestSpecial(inner);   // recurse on inner
                blocks.push_back("1" + inner + "0");
                start = i + 1;
            }
        }

        sort(blocks.begin(), blocks.end(), greater<string>()); // greedy
        string ans;
        for (auto &b : blocks) ans += b;
        return ans;
    }
};
