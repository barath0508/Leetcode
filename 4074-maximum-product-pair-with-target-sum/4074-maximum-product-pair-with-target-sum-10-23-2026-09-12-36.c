/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxProductPair(int* nums, int numsSize, int target, int* returnSize) {
    int *ans = malloc(2 * sizeof(int));
    *returnSize = 2;

    ans[0] = -1;
    ans[1] = -1;

    int found = 0;
    long long max = 0;

    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            if (i == j) continue;

            if (nums[i] + nums[j] == target && nums[i] > nums[j]) {
                long long product = (long long)nums[i] * nums[j];

                if (!found || product > max) {
                    found = 1;
                    max = product;
                    ans[0] = i;
                    ans[1] = j;
                }
            }
        }
    }

    return ans;
}