class Solution {
    public char nextGreatestLetter(char[] letters, char target) {
        int n = letters.length;
        int left = 0, right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (letters[mid] > target) {
                // mid is a candidate, but there might be a smaller index on the left
                right = mid - 1;
            } else {
                // letters[mid] <= target, need to search to the right
                left = mid + 1;
            }
        }

        // left is now the index of the first letter > target,
        // or n if no such letter exists -> wrap to index 0 using modulo
        return letters[left % n];
    }
}
