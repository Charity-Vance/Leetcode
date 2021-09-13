int cnt = 0;

void findTarget( int *nums, int target, int n, int numsSize ){
    if( *num == target ){
        cnt++;
    }
    else if( n < numsSize ){
        findTarget( nums, target, 0, numsSize );

    }
}

int findTargetSumWays(int* nums, int numsSize, int target){

    findTarget( nums, target, 0, numsSize );

    return cnt;
}
