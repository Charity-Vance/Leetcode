void Swap( int *_a, int *_b ){
    int _c = 0;
    _c = *_a;
    *_a = *_b;
    *_b = _c;
}

int cmp ( const void *a , const void *b ) 
{ 
    return *(int*)a - *(int*)b; 
} 
void nextPermutation(int* nums, int numsSize){
    int i = numsSize - 1;
    int j = numsSize - 1;

    /*第一次交换，寻找后一个数比前一个数大的位置*/
    for( ; i>0; i-- ){
        if( nums[i-1] < nums[i] ){
            Swap( &nums[i-1], &nums[i] );
            break;
        }
    }
    /*第二次交换，确保该位置的数为最小数*/
    if( i != 0 ){
        for( ; j>i; j-- ){
            if( nums[j] < nums[i-1] && nums[j] > nums[i] ){
                Swap( &nums[i-1], &nums[j] );
            }
        }
    }
    qsort( &nums[i], numsSize-i, sizeof(nums[i]), cmp );
}