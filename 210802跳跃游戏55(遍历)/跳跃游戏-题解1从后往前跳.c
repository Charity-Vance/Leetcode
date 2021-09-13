//从后往前跳
bool canJump(int* nums, int numsSize){
    int min = numsSize - 1;
    for(int i = numsSize - 2; i > 0; --i) {
        if(i + nums[i] >= min) {
            min = i;
        }
    }
    return nums[0] >= min;
}

作者：hamiguaex163com
链接：https://leetcode-cn.com/problems/jump-game/solution/cong-qian-cong-hou-du-xing-a-by-hamiguaex163com/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。