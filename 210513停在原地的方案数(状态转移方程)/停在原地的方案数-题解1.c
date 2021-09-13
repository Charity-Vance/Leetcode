/*
*p[i][j]表示在i步操作之后，指针位于下标j的方案数
i的取值范围是0≤i≤stepsj的取值范围是0≤j≤arrLen−1
*状态转移方程
    dp[i][j]=dp[i−1][j−1]+dp[i−1][j]+dp[i−1][j+1]
*/

const int MODULO = 1000000007;

int numWays(int steps, int arrLen) 
{
    int maxColumn = fmin(arrLen - 1, steps);
    int dp[steps + 1][maxColumn + 1];   //dp[i][j]表示在i步操作之后，指针位于下标j的方案数
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;       //起始位置，方案数为1
    for (int i = 1; i <= steps; i++)    //步数从1到steps；
    {
        for (int j = 0; j <= maxColumn; j++) 
        {
            dp[i][j] = dp[i - 1][j];    //原地不动
            if (j - 1 >= 0)             //往右走，需要原先左边存在
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MODULO;
            }
            if (j + 1 <= maxColumn)     //往左走，需要原先右边存在
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % MODULO;
            }
        }
    }
    return dp[steps][0];
}
