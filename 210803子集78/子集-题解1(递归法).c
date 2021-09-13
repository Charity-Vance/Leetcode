int** ans;
int* ansColSize;
int ansSize;

int* t;
int tSize;

void dfs(int cur, int* nums, int numsSize) {
    if (cur == numsSize) {
        int* tmp = malloc(sizeof(int) * tSize);
        memcpy(tmp, t, sizeof(int) * tSize);
        ansColSize[ansSize] = tSize;
        ans[ansSize++] = tmp;
        return;
    }
    t[tSize++] = nums[cur];
    dfs(cur + 1, nums, numsSize);
    tSize--;
    dfs(cur + 1, nums, numsSize);
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    ans = malloc(sizeof(int*) * (1 << numsSize));
    ansColSize = malloc(sizeof(int) * (1 << numsSize));
    t = malloc(sizeof(int) * numsSize);
    *returnSize = 1 << numsSize;
    ansSize = tSize = 0;
    dfs(0, nums, numsSize);
    *returnColumnSizes = ansColSize;
    return ans;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/subsets/solution/zi-ji-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。