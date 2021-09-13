int maxProfit(int* prices, int pricesSize){
    if(pricesSize==0) return 0;
    int result=0,max=prices[0],min=prices[0];
    for(int i=1;i<pricesSize;i++)
    {
        if(prices[i]>max)   //股票价格上升了
        {
            max=prices[i];
            result=fmax(max-min,result);
        }
        else if(prices[i]<min)  //最低价格下降了
        {
            min=max=prices[i];
        }
    }
    return result;
}

作者：nuclear-30
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/cyu-yan-shi-xian-bian-li-yi-ci-by-nuclear-30/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。