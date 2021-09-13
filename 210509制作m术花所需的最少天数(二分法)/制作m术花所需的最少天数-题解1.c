/*二分查找
    每束花需要 kk 朵花，需要制作 mm 束花，因此一共需要 k \times mk×m 朵花。
如果花园中的花朵数量少于 k \times mk×m，即数组 \textit{bloomDay}bloomDay 的长度小于 k \times mk×m，
则无法制作出指定数量的花束，返回 -1−1。如果数组 \textit{bloomDay}bloomDay 的长度大于或等于 k \times mk×m，
则一定可以制作出指定数量的花束。
    为了计算制作出指定数量的花束的最少天数，首先需要实现一个辅助函数用于判断在给定的天数内能否制作出指定数量的花束，
辅助函数的参数除了 \textit{bloomDay}bloomDay、mm 和 kk 之外，还有一个参数 \textit{days}days 表示指定天数。
例如，当 \textit{bloomDay}=[1,10,3,10,2]bloomDay=[1,10,3,10,2]、m=3m=3、k=1k=1 时，
如果 \textit{days}=3days=3 则辅助函数返回 \text{true}true，
如果 \textit{days}=2days=2 则辅助函数返回 \text{false}false。
    对于辅助函数的实现，可以遍历数组 \textit{bloomDay}bloomDay，
计算其中的长度为 kk 且最大元素不超过 \textit{days}days 的不重合的连续子数组的数量，
如果符合要求的不重合的连续子数组的数量大于或等于 mm 则返回 \text{true}true，否则返回 \text{false}false。
    当 \textit{days}days 很小的时候，辅助函数总是返回 \text{false}false，
因为天数太少不能收齐 mm 个花束；当 \textit{days}days 很大的时候，
辅助函数总是返回 \text{true}true，如果给定序列可以制作出 mm 个花束。
在 \textit{days}days 慢慢变大的过程中，辅助函数的返回值会从 \text{false}false 变成 \text{true}true，
所以我们可以认为这个辅助函数是关于 \textit{days}days 递增的，于是可以通过二分查找得到最少天数。
在确保可以制作出指定数量的花束的情况下，所需的最少天数一定不会小于数组 \textit{bloomDay}bloomDay 中的最小值，
一定不会大于数组 \textit{bloomDay}bloomDay 中的最大值，因此二分查找的初始值是 \textit{low}low 等于数组 \textit{bloomDay}bloomDay 中的最小值，
\textit{high}high 等于数组 \textit{bloomDay}bloomDay 中的最大值。
    当 \textit{low}low 和 \textit{high}high 的值相等时，二分查找结束，此时 \textit{low}low 的值即为最少天数。
*/
bool canMake(int* bloomDay, int bloomDaySize, int days, int m, int k) {
    int bouquets = 0;
    int flowers = 0;
    int length = bloomDaySize;
    for (int i = 0; i < length && bouquets < m; i++) {
        if (bloomDay[i] <= days) {
            flowers++;
            if (flowers == k) {
                bouquets++;
                flowers = 0;
            }
        } else {
            flowers = 0;
        }
    }
    return bouquets >= m;
}

int minDays(int* bloomDay, int bloomDaySize, int m, int k) {
    if (m > bloomDaySize / k) {
        return -1;
    }
    int low = INT_MAX, high = 0;
    for (int i = 0; i < bloomDaySize; i++) {
        low = fmin(low, bloomDay[i]);
        high = fmax(high, bloomDay[i]);
    }
    while (low < high) {
        int days = (high - low) / 2 + low;
        if (canMake(bloomDay, bloomDaySize, days, m, k)) {
            high = days;
        } else {
            low = days + 1;
        }
    }
    return low;
}
