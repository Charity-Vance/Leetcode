int swap( int *a, int *b ){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void sortColors(int* nums, int numsSize){
    int left = 0;
    int right = numsSize - 1;
    int i = 0;

    for( i=0; i<numsSize; i++ ){
        if( nums[i] == 0 ){
            swap( nums[i], nums[left] );
            
        }
    }


}