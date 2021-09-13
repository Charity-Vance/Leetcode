bool stoneGame(int* piles, int pilesSize) {
    int dp[pilesSize][pilesSize];
    for (int i = 0; i < pilesSize; i++) {
        dp[i][i] = piles[i];
    }
    for (int i = pilesSize - 2; i >= 0; i--) {
        for (int j = i + 1; j < pilesSize; j++) {
            dp[i][j] = fmax(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
        }
    }
    return dp[0][pilesSize - 1] > 0;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/stone-game/solution/shi-zi-you-xi-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。