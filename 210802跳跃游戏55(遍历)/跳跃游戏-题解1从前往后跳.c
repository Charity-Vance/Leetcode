//从前往后跳
bool canJump(int* nums, int numsSize){
    int max = nums[0];
    for(int i = 1; i < numsSize; ++i) {
        if(i > max) {
            return false;
        }
        if(i + nums[i] > max) {
            max = i + nums[i];
        }
    }
    return true;
}

作者：hamiguaex163com
链接：https://leetcode-cn.com/problems/jump-game/solution/cong-qian-cong-hou-du-xing-a-by-hamiguaex163com/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
