int maxSubArray(int* nums, int numsSize){

    int res[numsSize+1];
    int v_min, v_max;
    int min_pos=0, max_pos=0;
    int i, j;

    // if( numsSize == 1 )
    //     return *nums;

    res[0] = 0;
    v_min = v_max = nums[0];
    for( i=0; i<numsSize; i++ ){
        res[i+1] = res[i] + nums[i];
        if( res[i] < v_min ){
            v_min = res[i];
            min_pos = i;            
        }
        if( res[i] > v_max ){
            v_max = res[i];
            max_pos = i;
        }
    }
    return (v_max - v_min);
}