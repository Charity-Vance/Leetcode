int next(int* nums, int numsSize, int cur) {
    return ((cur + nums[cur]) % numsSize + numsSize) % numsSize;  // 保证返回值在 [0,n) 中
}

bool circularArrayLoop(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        if (!nums[i]) {
            continue;
        }
        int slow = i, fast = next(nums, numsSize, i);
        // 判断非零且方向相同
        while (nums[slow] * nums[fast] > 0 && nums[slow] * nums[next(nums, numsSize, fast)] > 0) {
            if (slow == fast) {
                if (slow != next(nums, numsSize, slow)) {
                    return true;
                } else {
                    break;
                }
            }
            slow = next(nums, numsSize, slow);
            fast = next(nums, numsSize, next(nums, numsSize, fast));
        }
        int add = i;
        while (nums[add] * nums[next(nums, numsSize, add)] > 0) {
            int tmp = add;
            add = next(nums, numsSize, add);
            nums[tmp] = 0;
        }
    }
    return false;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/circular-array-loop/solution/huan-xing-shu-zu-shi-fou-cun-zai-xun-hua-0ay2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。