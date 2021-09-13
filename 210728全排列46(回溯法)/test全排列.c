//210728全排列46
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 #include<stdio.h>
 #include<stdlib.h>
 
int numsBit = 0x00;
int ansSize;
int combineSize;
int* ansColumnSize;

void dfs( int* nums, int** ans, int numsSize, int* combine, int numsBitSize ){
    int i = 0;
    if( (numsBit & numsBitSize) == numsBitSize ){ //每个数都被取到了，将该数复制到数组中
        int* tmp = malloc(sizeof(int) * numsSize);
        for( i=0; i<numsSize; i++ ){
            tmp[i] = combine[i];
        }
        ans[ansSize] = tmp;
        ansColumnSize[ansSize++] = numsSize;
        return;
    }
        
    for( i=0; i<numsSize; i++ ){
        if( (numsBit & 1<<i) == 0 ){    //找到哪一位没有被选择，继续搜索
            combine[combineSize++] = nums[i];
            numsBit |= 1<<i;
            dfs( nums, ans, numsSize, combine, numsBitSize );
            numsBit &= ~(1<<i);
            combineSize--;
        }
    }
}
int nums[3] = {1, 2, 3};
int numsSize = 3;
int* returnSize;
int** returnColumnSizes;
//int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
int main(void){
    int sum, i, n, numsBitSize;
    int** ans;
    int combine[10];
    ansSize = combineSize = 0;

    n = numsSize;
    sum = 1;

    for( i=0; i<n; i++ ){
        sum *= i+1;
        numsBitSize |= 1<<i;
    }
    sum += 1;
    //numsBitSize = ~numsBit;
    ans = malloc(sizeof(int* ) * sum);
    ansColumnSize = malloc(sizeof(int* ) * sum);
    dfs( nums, ans, n, combine, numsBitSize );

    *returnSize = ansSize;
    for( i=0; i<sum; i++ )  (*returnColumnSizes)[i] = numsSize;
	i = 0;
	i = 1;
	
//    return ans;
}
