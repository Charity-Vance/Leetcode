int maxProfit(int* prices, int pricesSize){
    int i, min_prices, max_prices, profit, max_profit;

    min_prices = prices[0];
    max_prices = prices[0];
    max_prices = profit = 0;
    for( i=0; i<pricesSize; i++ ){
        if( prices[i] < min_prices ){
            max_prices = min_prices = prices[i];
        }
        if( prices[i] > max_prices ){
            max_prices = prices[i];
        }
        profit = max_prices - min_prices;
        max_profit = profit > max_profit ? profit : max_profit;
    }
    return max_profit;
}
/*Test code*/
#include <stdio.h>
int prices[5] = {7,6,4,3,1};
int pricesSize = 5;
int main(){
    int i, min_prices, max_prices, profit, max_profit;

    min_prices = prices[0];
    max_prices = prices[0];
    max_prices = profit = 0;
    for( i=0; i<pricesSize; i++ ){
        if( prices[i] < min_prices ){
            max_prices = min_prices = prices[i];
        }
        if( prices[i] > max_prices ){
            max_prices = prices[i];
        }
        profit = max_prices - min_prices;
        max_profit = profit > max_profit ? profit : max_profit;
    }
    printf("%d\n", max_profit);
    return max_profit;

}
