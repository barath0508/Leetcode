class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        string ans;
        ans.reserve(n);

        for (int i = 0; i < n; ++i) {
            char c = nums[i][i];
            ans.push_back(c == '0' ? '1' : '0');
        }
        return ans;
    }
};
