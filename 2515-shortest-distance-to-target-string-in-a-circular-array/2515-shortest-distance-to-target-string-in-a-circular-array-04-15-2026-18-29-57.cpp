#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        int ans = n; // larger than any possible distance (max is n-1)

        for (int i = 0; i < n; ++i) {
            if (words[i] == target) {
                int direct = abs(i - startIndex); // straight distance
                int wrap   = n - direct;          // circular wrap distance
                int cur    = min(direct, wrap);   // best distance to this index
                ans = min(ans, cur);              // keep global minimum
            }
        }

        return (ans == n) ? -1 : ans;             // if never updated, target not found
    }
};