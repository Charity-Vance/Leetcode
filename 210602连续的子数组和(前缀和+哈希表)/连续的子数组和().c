bool checkSubarraySum(int* nums, int numsSize, int k){
   int i,j;
   int sum = 0;

   for( i=0; i<numsSize; i++ ){
       for( j=i; j<numsSize; j++ ){
           sum += nums[j];
           if( sum%k==0 ){
               return true;
           }
        }
        sum = 0;
   }
   return false;
}

/*test code*/
int nums[5] = {23, 2, 4, 6, 6};
int numsSize = 5;
int k = 7;

int main(){
    int i,j;
    int sum = 0;

    for( i=0; i<numsSize; i++ ){
        for( j=i; j<numsSize; j++ ){
            sum += nums[j];
            if( sum%k==0 && sum!=0 ){
                return 1;
            }
            sum = 0;
        }
    }
    return 0;

}
