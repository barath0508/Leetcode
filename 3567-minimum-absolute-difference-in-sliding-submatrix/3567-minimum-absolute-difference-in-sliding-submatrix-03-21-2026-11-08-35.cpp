class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int R = m - k + 1, C = n - k + 1;
        vector<vector<int>> ans(R, vector<int>(C));

        unordered_map<int,int> cnt;
        set<int> S;
        multiset<int> G;

        auto addGap = [&](int d) {
            if (d >= 0) G.insert(d);
        };
        auto removeGap = [&](int d) {
            auto it = G.find(d);
            if (it != G.end()) G.erase(it);
        };

        auto insertVal = [&](int x) {
            int &c = cnt[x];
            if (c++ > 0) return; // already present as distinct
            auto it = S.lower_bound(x);
            int prevExists = (it != S.begin());
            int nextExists = (it != S.end());
            int prevVal, nextVal;
            if (prevExists) {
                auto it2 = it; --it2;
                prevVal = *it2;
            }
            if (nextExists) {
                nextVal = *it;
            }
            if (prevExists && nextExists) {
                removeGap(nextVal - prevVal);
                addGap(x - prevVal);
                addGap(nextVal - x);
            } else if (prevExists) {
                addGap(x - prevVal);
            } else if (nextExists) {
                addGap(nextVal - x);
            }
            S.insert(x);
        };

        auto eraseVal = [&](int x) {
            auto itCnt = cnt.find(x);
            if (itCnt == cnt.end()) return;
            if (--itCnt->second > 0) return;
            cnt.erase(itCnt);

            auto it = S.find(x);
            if (it == S.end()) return;
            bool hasPrev = (it != S.begin());
            bool hasNext = (next(it) != S.end());
            int prevVal, nextVal;
            if (hasPrev) {
                auto it2 = it; --it2;
                prevVal = *it2;
            }
            if (hasNext) {
                nextVal = *next(it);
            }
            if (hasPrev && hasNext) {
                removeGap(x - prevVal);
                removeGap(nextVal - x);
                addGap(nextVal - prevVal);
            } else if (hasPrev) {
                removeGap(x - prevVal);
            } else if (hasNext) {
                removeGap(nextVal - x);
            }
            S.erase(it);
        };

        auto windowAns = [&]() -> int {
            if (S.size() <= 1) return 0;
            return *G.begin();
        };

        for (int top = 0; top < R; ++top) {
            cnt.clear(); S.clear(); G.clear();
            for (int i = top; i < top + k; ++i)
                for (int j = 0; j < k; ++j)
                    insertVal(grid[i][j]);
            ans[top][0] = windowAns();

            for (int left = 0; left + 1 < C; ++left) {
                int removeCol = left;
                int addCol = left + k;
                for (int i = top; i < top + k; ++i) {
                    eraseVal(grid[i][removeCol]);
                    insertVal(grid[i][addCol]);
                }
                ans[top][left + 1] = windowAns();
            }
        }

        return ans;
    }
};
