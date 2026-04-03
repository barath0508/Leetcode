class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        vector<pair<long long,long long>> rob(n);
        for (int i = 0; i < n; ++i) {
            rob[i] = {robots[i], distance[i]};
        }
        sort(rob.begin(), rob.end());
        sort(walls.begin(), walls.end());

        int m = walls.size();
        auto lb = [&](long long x) {
            return (int)(lower_bound(walls.begin(), walls.end(), x) - walls.begin());
        };

        // dp[i][dirNext]: best using robots[0..i] given robot i+1 will shoot dirNext
        // dirNext = 0 -> next shoots left, 1 -> next shoots right
        const int NEG_INF = -(1e9);
        vector<array<int,2>> dp(n);

        // base for i = 0
        for (int dirNext = 0; dirNext < 2; ++dirNext) {
            long long p = rob[0].first;
            long long d = rob[0].second;

            // shoot left for robot 0
            long long leftBoundary = p - d;
            int wallsLeft = 0;
            if (leftBoundary <= p) {
                int L = lb(leftBoundary);
                int R = lb(p + 1);
                wallsLeft = R - L;
            }
            int valLeft = wallsLeft; // no previous robots

            // shoot right for robot 0
            long long rightBoundary = p + d;
            if (1 < n) {
                long long pn = rob[1].first;
                long long dn = rob[1].second;
                if (dirNext == 0) {
                    rightBoundary = min(rightBoundary, pn - dn - 1);
                } else {
                    rightBoundary = min(rightBoundary, pn - 1);
                }
            }
            int wallsRight = 0;
            if (rightBoundary >= p) {
                int L = lb(p);
                int R = lb(rightBoundary + 1);
                wallsRight = R - L;
            }
            int valRight = wallsRight;

            dp[0][dirNext] = max(valLeft, valRight);
        }

        // fill for i = 1..n-1
        for (int i = 1; i < n; ++i) {
            for (int dirNext = 0; dirNext < 2; ++dirNext) {
                long long p = rob[i].first;
                long long d = rob[i].second;

                // shoot left
                long long leftBoundary = p - d;
                leftBoundary = max(leftBoundary, rob[i-1].first + 1);
                int wallsLeft = 0;
                if (leftBoundary <= p) {
                    int L = lb(leftBoundary);
                    int R = lb(p + 1);
                    wallsLeft = R - L;
                }
                int valLeft = dp[i-1][0] + wallsLeft;

                // shoot right
                long long rightBoundary = p + d;
                if (i + 1 < n) {
                    long long pn = rob[i+1].first;
                    long long dn = rob[i+1].second;
                    if (dirNext == 0) {
                        rightBoundary = min(rightBoundary, pn - dn - 1);
                    } else {
                        rightBoundary = min(rightBoundary, pn - 1);
                    }
                }
                int wallsRight = 0;
                if (rightBoundary >= p) {
                    int L = lb(p);
                    int R = lb(rightBoundary + 1);
                    wallsRight = R - L;
                }
                int valRight = dp[i-1][1] + wallsRight;

                dp[i][dirNext] = max(valLeft, valRight);
            }
        }

        // final answer: all robots used, no robot after n-1, assume "next" dir = 1
        return dp[n-1][1];
    }
};