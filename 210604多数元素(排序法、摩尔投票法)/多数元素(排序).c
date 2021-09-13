int cmp_int(const void* _a , const void* _b)    //参数格式固定
{
    int* a = (int*)_a;    //强制类型转换
    int* b = (int*)_b;
    return *a - *b;
}

int majorityElement(int* nums, int numsSize){

    qsort( nums, numsSize, sizeof(nums[0]), cmp_int ); 

    return nums[numsSize/2];

}

/*testcode*/
int nums[10] = {1,1,2,3,5,3,5,1,6,4};
int numsSize = 10;
int main(){

    qsort( nums, numsSize, sizeof(nums[0]), cmp_int ); 

    return nums[numsSize/2];

}