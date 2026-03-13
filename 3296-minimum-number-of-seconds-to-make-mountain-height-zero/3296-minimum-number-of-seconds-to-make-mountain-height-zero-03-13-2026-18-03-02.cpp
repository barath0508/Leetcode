class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        using ll = long long;
        sort(workerTimes.begin(), workerTimes.end()); // optional, but common

        auto can = [&](ll T) -> bool {
            ll total = 0;
            for (int w : workerTimes) {
                // maximum k such that w * k * (k + 1) / 2 <= T
                long double val = (long double)T * 2.0L / (long double)w + 0.25L;
                ll k = (ll)(sqrt(val) - 0.5L); // floor automatically via cast

                if (k <= 0) continue;
                total += k;
                if (total >= mountainHeight) return true;
            }
            return total >= mountainHeight;
        };

        ll lo = 1, hi = (ll)1e16;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (can(mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
};
