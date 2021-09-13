#define MAXNUM 200000

bool canJump(int* nums, int numsSize){
    int i, j, n;

    n = numsSize;
    if( n== 1 )
        return true;

    for( i=0; (i+1<n)&&(i<nums[0]); i++ ){
        nums[i+1] += MAXNUM;
    }
    for( i=0; i<n-1; i++ ){
        if( nums[i] <= MAXNUM ) continue;
        nums[i] %= MAXNUM;
        for( j=0; (j+1<n)&&(j<nums[i]); j++ ){
            nums[i+1+j] = (nums[i+1+j]%MAXNUM)+MAXNUM;
        }
    }
    if( nums[n-1] >= MAXNUM )
        return true;
    return false;
}
//[3,2,1,0,4]
