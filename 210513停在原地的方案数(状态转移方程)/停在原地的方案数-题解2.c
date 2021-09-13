const int MODULO = 1000000007;

int numWays(int steps, int arrLen) {
    int maxColumn = fmin(arrLen - 1, steps);
    int dp[maxColumn + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 1; i <= steps; i++) {
        int dpNext[maxColumn + 1];
        for (int j = 0; j <= maxColumn; j++) {
            dpNext[j] = dp[j];
            if (j - 1 >= 0) {
                dpNext[j] = (dpNext[j] + dp[j - 1]) % MODULO;
            }
            if (j + 1 <= maxColumn) {
                dpNext[j] = (dpNext[j] + dp[j + 1]) % MODULO;
            }
        }
        memcpy(dp, dpNext, sizeof(dp));
    }
    return dp[0];
}
