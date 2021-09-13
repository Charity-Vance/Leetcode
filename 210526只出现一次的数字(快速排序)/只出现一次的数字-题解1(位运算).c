int singleNumber(int* nums, int numsSize){
    int ans = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        ans ^= nums[i];
    }
    return ans;
}

作者：Dine
链接：https://leetcode-cn.com/problems/single-number/solution/136-zhi-chu-xian-yi-ci-de-shu-zi-by-dine-mzeo/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。