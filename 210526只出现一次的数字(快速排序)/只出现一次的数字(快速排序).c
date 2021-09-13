void QuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
            {
                j--;
            }
 
            if(i < j)
            {
                arr[i++] = arr[j];
            }
 
            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }
 
            if(i < j)
            {
                arr[j--] = arr[i];
            }
        }
 
        arr[i] = k;
 
        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}

int singleNumber(int* nums, int numsSize){
    int i;

    QuickSort( nums, 0, numsSize-1 );
    if( nums[0] != nums[1] ){
        return nums[0];
    }
    for( i=1; i<numsSize-1; i++ ){
        if( nums[i-1]!=nums[i] && nums[i]!=nums[i+1] )
            break;
    }
    return nums[i];
}
/*testcode*/
#include<stdio.h>
int nums[3] = {2,2,1};
int numsSize = 3;
int main(){
    int i;

    QuickSort( nums, 0, numsSize-1 );
    if( nums[0] != nums[1] ){
        return nums[0];
    }
    for( i=1; i<numsSize-1; i++ ){
        if( nums[i-1]!=nums[i] && nums[i]!=nums[i+1] )
            break;
    }
    printf( "%d\n", nums[i] );
    //return nums[i];
}
