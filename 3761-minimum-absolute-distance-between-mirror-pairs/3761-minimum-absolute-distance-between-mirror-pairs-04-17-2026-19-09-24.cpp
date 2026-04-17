class Solution {
public:
    long long reverseDigits(long long x) {
        long long rev = 0;
        while (x > 0) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        return rev;
    }

    int minMirrorPairDistance(vector<int>& nums) {  // <- NAME MUST MATCH WRAPPER
        unordered_map<long long, int> mp;
        int ans = INT_MAX;

        for (int i = 0; i < (int)nums.size(); ++i) {
            long long x = nums[i];

            // If we've seen some j with reverse(nums[j]) == x,
            // mp[x] = j and (j, i) is a mirror pair.
            if (mp.count(x)) {
                ans = min(ans, i - mp[x]);
            }

            long long rev = reverseDigits(x);

            // Store/update current index under key reverse(nums[i])
            mp[rev] = i;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};