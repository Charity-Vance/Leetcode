int findMaximumXOR(int* nums, int numsSize)
{
    int maxnum = 0;
    int i,j;

    for( i=0; i<numsSize; i++ )
    {
        for( j=i; j<numsSize; j++ )
        {
            maxnum = maxnum>(nums[i]^nums[j])?maxnum:(nums[i]^nums[j]);
        }
    }
    return maxnum;
}

/*超出时间限制
*  时间复杂度O(n^2)s
*/