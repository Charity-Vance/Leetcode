int profitableSchemes(int n, int minProfit, int* group, int groupSize, int* profit, int profitSize) {
    int len = groupSize, MOD = (int)1e9 + 7;
    int dp[len + 1][n + 1][minProfit + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 1; i <= len; i++) {
        int members = group[i - 1], earn = profit[i - 1];
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= minProfit; k++) {
                if (j < members) {
                    dp[i][j][k] = dp[i - 1][j][k];
                } else {
                    dp[i][j][k] = (dp[i - 1][j][k] + dp[i - 1][j - members][(int)fmax(0, k - earn)]) % MOD;
                }
            }
        }
    }
    int sum = 0;
    for (int j = 0; j <= n; j++) {
        sum = (sum + dp[len][j][minProfit]) % MOD;
    }
    return sum;
}
