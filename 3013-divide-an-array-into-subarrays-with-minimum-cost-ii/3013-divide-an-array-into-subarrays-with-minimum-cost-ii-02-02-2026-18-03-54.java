import java.util.*;

class Solution {
    // Heaps as fields so helper can update sumBig
    private PriorityQueue<int[]> big;   // max-heap (selected k-2 smallest)
    private PriorityQueue<int[]> small; // min-heap (others in window)
    private long sumBig;

    // Remove elements whose index < leftBound from both heaps
    private void cleanHeaps(int leftBound) {
        while (!big.isEmpty() && big.peek()[1] < leftBound) {
            int[] top = big.poll();
            sumBig -= top[0];
        }
        while (!small.isEmpty() && small.peek()[1] < leftBound) {
            small.poll();
        }
    }

    public long minimumCost(int[] nums, int k, int dist) {
        int n = nums.length;
        long base = nums[0];

        int need = k - 2;
        if (need == 0) {
            long ans = Long.MAX_VALUE;
            for (int i = 1; i < n; i++) {
                ans = Math.min(ans, base + nums[i]);
            }
            return ans;
        }

        big = new PriorityQueue<>((a, b) -> Integer.compare(b[0], a[0]));      // by value desc
        small = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));       // by value asc
        sumBig = 0L;
        long ans = Long.MAX_VALUE;

        int curR = 0;  // rightmost index inserted into heaps

        for (int i = 1; i < n; i++) {
            int L = i + 1;
            int R = Math.min(n - 1, i + dist);
            if (L > R) continue;   // no space for remaining starts

            // expand right side of window
            while (curR < R) {
                curR++;
                small.offer(new int[]{nums[curR], curR});
            }

            // drop indices < L from both heaps
            cleanHeaps(L);

            // ensure big has exactly 'need' smallest values from current window
            while (big.size() < need && !small.isEmpty()) {
                // clean small top lazily here too
                while (!small.isEmpty() && small.peek()[1] < L) {
                    small.poll();
                }
                if (small.isEmpty()) break;

                int[] x = small.poll();
                big.offer(x);
                sumBig += x[0];
            }
            if (big.size() < need) continue; // not enough candidates

            // rebalance: all values in big must be <= all in small
            while (true) {
                // clean lazy deletions on both tops every iteration
                while (!big.isEmpty() && big.peek()[1] < L) {
                    int[] top = big.poll();
                    sumBig -= top[0];
                }
                while (!small.isEmpty() && small.peek()[1] < L) {
                    small.poll();
                }
                if (big.isEmpty() || small.isEmpty()) break;

                if (big.peek()[0] <= small.peek()[0]) break;

                int[] fromBig = big.poll();
                int[] fromSmall = small.poll();

                sumBig -= fromBig[0];
                sumBig += fromSmall[0];

                big.offer(fromSmall);
                small.offer(fromBig);
            }

            if (big.size() == need) {
                long cand = base + nums[i] + sumBig;
                ans = Math.min(ans, cand);
            }
        }

        return ans;
    }
}
