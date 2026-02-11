class SegmentTree {
public:
    struct Node {
        int mn, mx, lazy;
    };

    int n;
    vector<Node> st;

    SegmentTree(int n) : n(n) {
        st.assign(4 * n, {0, 0, 0});
    }

    void apply(int p, int val) {
        st[p].mn += val;
        st[p].mx += val;
        st[p].lazy += val;
    }

    void push(int p) {
        if (st[p].lazy != 0) {
            int v = st[p].lazy;
            apply(p << 1, v);
            apply(p << 1 | 1, v);
            st[p].lazy = 0;
        }
    }

    void pull(int p) {
        st[p].mn = min(st[p << 1].mn, st[p << 1 | 1].mn);
        st[p].mx = max(st[p << 1].mx, st[p << 1 | 1].mx);
    }

    void rangeAdd(int p, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(p, val);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        rangeAdd(p << 1, l, m, ql, qr, val);
        rangeAdd(p << 1 | 1, m + 1, r, ql, qr, val);
        pull(p);
    }

    void rangeAdd(int l, int r, int val) {
        if (l > r) return;
        rangeAdd(1, 0, n - 1, l, r, val);
    }

    // Find rightmost index >= ql with value == 0, or -1 if none
    int findRightmostZero(int p, int l, int r, int ql) {
        if (r < ql || st[p].mn > 0 || st[p].mx < 0) return -1;
        if (l == r) {
            // since mn <= 0 <= mx, value must be 0
            return l;
        }
        push(p);
        int m = (l + r) >> 1;
        // try right child first for rightmost
        int res = -1;
        if (ql <= r) {
            res = findRightmostZero(p << 1 | 1, m + 1, r, ql);
            if (res != -1) return res;
        }
        return findRightmostZero(p << 1, l, m, ql);
    }

    int findRightmostZero(int ql) {
        return findRightmostZero(1, 0, n - 1, ql);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        const int MAXV = 100000;  // as per constraints

        vector<vector<int>> pos(MAXV + 1);
        for (int i = 0; i < n; ++i) {
            pos[nums[i]].push_back(i);
        }

        SegmentTree st(n);

        // initialize contributions for l = 0
        for (int v = 1; v <= MAXV; ++v) {
            if (pos[v].empty()) continue;
            int firstPos = pos[v][0];
            int sign = (v % 2 ? +1 : -1);
            st.rangeAdd(firstPos, n - 1, sign);
        }

        int ans = 0;

        // For each l, query and then slide
        for (int l = 0; l < n; ++l) {
            // query rightmost r >= l with diff == 0
            int r = st.findRightmostZero(l);
            if (r != -1) {
                ans = max(ans, r - l + 1);
            }

            int x = nums[l];
            int sign = (x % 2 ? +1 : -1);

            // pop this occurrence from pos[x]
            auto &vec = pos[x];
            // vec[0] should be l
            if (!vec.empty() && vec[0] == l) {
                vec.erase(vec.begin());
            }

            int next = vec.empty() ? n : vec[0];
            // remove x's contribution for all r < next
            st.rangeAdd(0, next - 1, -sign);
        }

        return ans;
    }
};
