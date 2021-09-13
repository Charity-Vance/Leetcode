int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int m = nums1Size, n = nums2Size;
    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++) {
        int num1 = nums1[i - 1];
        for (int j = 1; j <= n; j++) {
            int num2 = nums2[j - 1];
            if (num1 == num2) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}