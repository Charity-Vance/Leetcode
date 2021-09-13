/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize){
    int i, j, n, pre, next;

    n = numsSize;
    pre = 0;
    next = nums[pre] - 1;
    for( i=0; i<n; i++ ){
        pre = i;
        if( nums[pre] != -1 ){
            next = nums[pre] - 1;
            while( nums[next] != -1 ){
                pre = next;
                next = nums[pre] - 1;
                nums[pre] = -1;
            }
        }
    }
    for( i=0,j=0; i<n; i++ ){
        if( nums[i] != -1 ){
            nums[j++] = i+1;
        }
    }
    *returnSize = j;
    return nums;
}

int cmp_int(const void* _a , const void* _b)    //参数格式固定
{
    int* a = (int*)_a;    //强制类型转换
    int* b = (int*)_b;
    return *a - *b;
}
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize){

    int i, j;

    qsort( nums, numsSize, sizeof(nums[0]), cmp_int ); 

    for( i=0,j=0; i<numsSize; i++ ){

    }

}