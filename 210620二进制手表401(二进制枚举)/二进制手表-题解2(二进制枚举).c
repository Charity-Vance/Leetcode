/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** readBinaryWatch(int turnedOn, int* returnSize) {
    char** ans = malloc(sizeof(char*) * 12 * 60);
    *returnSize = 0;
    for (int i = 0; i < 1024; ++i) {
        int h = i >> 6, m = i & 63;  // 用位运算取出高 4 位和低 6 位
        if (h < 12 && m < 60 && __builtin_popcount(i) == turnedOn) {
            char* tmp = malloc(sizeof(char) * 6);
            sprintf(tmp, "%d:%02d", h, m);
            ans[(*returnSize)++] = tmp;
        }
    }

    return ans;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/binary-watch/solution/er-jin-zhi-shou-biao-by-leetcode-solutio-3559/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。