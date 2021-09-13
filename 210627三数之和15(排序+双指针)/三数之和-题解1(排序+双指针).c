/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 /* qsort的比较函数 */
int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    /* 先记录返回的行数为0 */
    *returnSize = 0;
    /* 输入为空、或元素个数小于3则返回NULL */
    if (nums == NULL || numsSize < 3) {
        return NULL;
    }
    /* 将nums排序为升序排列 */
    qsort(nums, numsSize, sizeof(int), cmp);
    /* 分配返回数组、返回数组的列数 */
    int** ret = (int**)malloc(numsSize * numsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(numsSize * numsSize *sizeof(int));
    /* 排序后的数组从头到尾进行遍历 */
    for (int i = 0; i < numsSize; i++) {
        /* 当前数组大于0，表示后续没有三数之和为0，结束遍历 */
        if (nums[i] > 0) {
            break;
        }
        /* 当前元素与上一次相等，跳过此次计算，去重 */
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        /* 定义左右指针 */
        int left = i + 1, right = numsSize - 1;
        /* 开始查找三数之和为0 */
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                ret[*returnSize] = (int*)malloc(sizeof(int) * 3);
                ret[*returnSize][0] = nums[i];
                ret[*returnSize][1] = nums[left];
                ret[*returnSize][2] = nums[right];
                /* 返回数组当前行的列数为3 */
                (*returnColumnSizes)[*returnSize] = 3;
                /* 返回数组的行数自加1 */
                (*returnSize)++;
                /* 对左右指针进行去重 */
                while (left < right && nums[left]  == nums[++left]);
                while (left < right && nums[right] == nums[--right]);
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return ret;
}

作者：zhangdengyu
链接：https://leetcode-cn.com/problems/3sum/solution/15-san-shu-zhi-he-by-dyzahng-xmz9/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。