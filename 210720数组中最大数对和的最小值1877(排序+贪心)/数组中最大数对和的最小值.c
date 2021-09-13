int cmp(int *a, int *b) {
    return *a - *b;
}

int cmp( const void *_a, const void *_b ){
    int *a = (int *)_a;
    int *b = (int *)_b;
    return *a - *b;
}

/*该比较算法有问题*/
int cmp( const void *a, const void *b ){
   return (int *)a - (int *)b; 
}

int minPairSum(int* nums, int numsSize){
    int i, n = numsSize/2, f_max = 0, data;
    qsort( nums, numsSize, sizeof(int), cmp );
    for( i=0; i<n; i++ ){
        data = nums[i] + nums[2*n-1-i];
        f_max = f_max > data ? f_max : data;
    }
    return f_max;
}