int hammingDistance(int x, int y) {
    int s = x ^ y, ret = 0;
    while (s) {
        s &= s - 1;
        ret++;
    }
    return ret;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/hamming-distance/solution/yi-ming-ju-chi-by-leetcode-solution-u1w7/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。