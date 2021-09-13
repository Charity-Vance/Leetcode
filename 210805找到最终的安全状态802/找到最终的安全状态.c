/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int n = numsSize;
    // int sum[11] = {1};
    int i, j, k, pos, len;

    int **ret = (int **)malloc(sizeof(int *) * (1 << numsSize));
    int *arraysize = (int *)malloc(sizeof(int ) * (1 << numsSize));

    ret[0] = (int *)malloc(sizeof(int));
    arraysize[0] = 0;
    ret[1] = (int *)malloc(sizeof(int));
    ret[1][0] = nums[0];
    len = 2;

    for( i=1; i<(1<<numsSize); i++ ){
        for( j=0; j<2*i; j++ ){
            pos = (1<<i) + j;
            int *ans = (int *)malloc(sizeof(int) * (j+1));
            memcpy( ans, ret[j], sizeof(ret[j])/sizeof(int));
            ans[j] = i;
            memcpy( ret[pos], ans, j+1 );
            arraysize[len++] = j+1;
        }
    }
    *returnColumnSizes = arraysize;
    *returnSize = len;

    return ret;
}

