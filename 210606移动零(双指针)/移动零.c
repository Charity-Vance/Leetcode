void moveZeroes(int* nums, int numsSize){
    int i, j;

    for( i=0,j=0; i<numsSize; i++ ){
        if( nums[i] != 0 ){
            nums[j++] = nums[i];
        }
    }
    for( i=j; i<numsSize; i++ ){
        nums[i] = 0;
    }
    return nums;
}
void moveZeroes(int* nums, int numsSize){
    int i, j;
    if( numsSize <= 1 ){
        return nums;
    }
    for( i=0,j=0; i<numsSize; i++ ){
        if( nums[i] != 0 ){
            nums[j++] = nums[i];
            nums[i] = 0;
        }
    }
    return nums;
}