#include<stdio.h>
#include<string.h> 
int change(int amount, int* coins, int coinsSize){
    int len = coinsSize;
    int i, j, num;
    int dp[amount + 1];

    memset(dp, 0, sizeof(dp)); 
    dp[0] = 1;
    for( i=1; i<=amount; i++ ){
        for( j=0; j<coinsSize; j++ ){
            num = coins[j];
            if( num <= i ){
                dp[i] += dp[i-num];
            }
        }
    }
    return dp[amount];
}

/*testcode*/
int amount = 5;
int coins[3] = {1, 2, 5 };
int coinsSize = 3;

int main(){
    int len = coinsSize;
    int i, j, num;
    int dp[amount + 1];

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for( i=1; i<amount+1; i++ ){
        for( j=0; j<len; j++ ){
            num = coins[j];
            if( num <= i ){
                dp[i] += dp[i-num];
            }
        }
    }
    return dp[amount];
}
