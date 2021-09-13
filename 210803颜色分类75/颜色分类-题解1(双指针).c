void swap(int *a, int *b) {
    int t = *a;
    *a = *b, *b = t;
}

void sortColors(int *nums, int numsSize) {
    int p0 = 0, p1 = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            swap(&nums[i], &nums[p1]);
            ++p1;
        } else if (nums[i] == 0) {
            swap(&nums[i], &nums[p0]);
            if (p0 < p1) {
            if (nums[i] == 1) {
                swap(&nums[i], &nums[p1]);
            }
            ++p0;
            ++p1;
        }
    }
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/sort-colors/solution/yan-se-fen-lei-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。