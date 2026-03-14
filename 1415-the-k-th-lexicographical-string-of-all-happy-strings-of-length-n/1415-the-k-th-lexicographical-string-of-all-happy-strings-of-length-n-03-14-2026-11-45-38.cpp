class Solution {
public:
    string getHappyString(int n, int k) {
        // total happy strings = 3 * 2^(n-1)
        int total = 3 * (1 << (n - 1));
        if (k > total) return "";

        string res;
        int block = 1 << (n - 1); // number of strings per first-char block

        // choose first character
        if (k <= block) {
            res.push_back('a');
        } else if (k <= 2 * block) {
            res.push_back('b');
            k -= block;
        } else {
            res.push_back('c');
            k -= 2 * block;
        }

        // choose remaining characters
        for (int i = 1; i < n; ++i) {
            block >>= 1; // each level halves the count

            char prev = res.back();
            // compute the two possible next chars in lexicographical order
            vector<char> candidates;
            for (char c : {'a', 'b', 'c'}) {
                if (c != prev) candidates.push_back(c);
            }

            // first candidate covers 'block' strings, second covers 'block' strings
            if (k <= block) {
                res.push_back(candidates[0]);
            } else {
                res.push_back(candidates[1]);
                k -= block;
            }
        }

        return res;
    }
};
