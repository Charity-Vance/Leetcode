void getZerosOnes(int* zerosOnes, char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        zerosOnes[str[i] - '0']++;
    }
}

int findMaxForm(char** strs, int strsSize, int m, int n) {
    int length = strsSize;
    int dp[length + 1][m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= length; i++) {
        int zerosOnes[2];
        memset(zerosOnes, 0, sizeof(zerosOnes));
        getZerosOnes(zerosOnes, strs[i - 1]);
        int zeros = zerosOnes[0], ones = zerosOnes[1];
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= n; k++) {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j >= zeros && k >= ones) {
                    dp[i][j][k] = fmax(dp[i][j][k], dp[i - 1][j - zeros][k - ones] + 1);
                }
            }
        }
    }
    return dp[length][m][n];
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/ones-and-zeroes/solution/yi-he-ling-by-leetcode-solution-u2z2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。