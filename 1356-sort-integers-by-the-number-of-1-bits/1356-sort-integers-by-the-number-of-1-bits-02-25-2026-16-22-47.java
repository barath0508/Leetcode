class Solution {
    private int bitCount(int x) {
        int cnt = 0;
        while (x != 0) {
            x &= (x - 1);
            cnt++;
        }
        return cnt;
    }

    public int[] sortByBits(int[] arr) {
        Integer[] tmp = new Integer[arr.length];
        for (int i = 0; i < arr.length; i++) tmp[i] = arr[i];

        Arrays.sort(tmp, (a, b) -> {
            int ca = bitCount(a);
            int cb = bitCount(b);
            if (ca == cb) return Integer.compare(a, b);
            return Integer.compare(ca, cb);
        });

        for (int i = 0; i < arr.length; i++) arr[i] = tmp[i];
        return arr;
    }
}
