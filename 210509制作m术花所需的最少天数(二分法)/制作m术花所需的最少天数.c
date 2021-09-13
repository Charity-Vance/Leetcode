/*运算有bug，
输入[1,10,3,10,2]
3
2
输出10
未采用二分法，时间超时
*/

int makeFlowers(int day, int* bloomDay, int bloomDaySize, int m, int k)
{
//    int* flowerday = malloc(sizeof(int) * bloomDaySize);
    int f_num = 0;      /*一束花中花的数量*/
    int f_bunch = 0;    /*几束花*/
    int i;

    for( i=0; i<bloomDaySize; i++ )
    {
        if( day >= bloomDay[i] )    /*满足天数要求且相邻*/
        {
            f_num++;
        }
        else
        {
            f_num = 0;      /*没满足要求，直接清零*/
        }
        if( f_num >= k )    /*集齐了相邻的k术花*/
        {
            f_num = 0;
            f_bunch++;
        }
    }
    if( f_bunch >= m )
        return 0;
    else
        return 1;
}

int minDays(int* bloomDay, int bloomDaySize, int m, int k){
    int i,maxday=0;
    int low = INT_MAX, high = 0;
    for (int i = 0; i < bloomDaySize; i++) 
    {
        low = fmin(low, bloomDay[i]);
        high = fmax(high, bloomDay[i]);
    }

    if( m*k > bloomDaySize )
    {
        return -1;
    }
    for( i=0; i<bloomDaySize; i++ )
    {
        maxday = bloomDay[i]>maxday?bloomDay[i]:maxday;
    }
    for( i=0; i<maxday; i++ )
    {
        if( !makeFlowers(i, bloomDay, bloomDaySize, m, k) )
            break;
    }
    if( i <= maxday )
        return i;
    else
        return -1;
}