#include<stdio.h>
#include<string.h> 
int change(int amount, int* coins, int coinsSize) {
    int dp[amount + 1];
    int i, j;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for ( i = 0; i < coinsSize; i++) {
        for ( j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[amount];
}

/*testcode*/
int amount = 5;
int coins[4] = {2, 3, 1, 5 };
int coinsSize = 4;

int main(){
	int k;
    int dp[amount + 1];
    int i, j;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for ( i = 0; i < coinsSize; i++) {
        for ( j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
            k=0;
        }
    }
    return dp[amount];
}
