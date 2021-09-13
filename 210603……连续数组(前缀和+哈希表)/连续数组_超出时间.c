int findMaxLength(int* nums, int numsSize){
   int i, j, n, m, maxnum;
   int flag = 0;
   n = numsSize;
   int arr[n];
   int sum = 0;

   maxnum = 0;
   for( i=0; i<numsSize; i++ ){
        if( nums[i] == 0 )
            arr[i] = -1;
        else if( nums[i] == 1 )
            arr[i] = 1;
        else
            arr[i] = 0;
   }
   for( i=0; i<numsSize; i++ ){
        for( j=i; j<numsSize; j++ ){
            if( arr[i] != 0 ){
                flag = 1;
            }
            m = j-i+1;
            sum += arr[j];
            if( sum==0 && flag==1 ){
                maxnum = maxnum > m ? maxnum : m;
            }
        }
        sum = 0;
   }
   return maxnum;
}

/*testcode*/
int nums[8] = {0,0,1,0,0,0,1,1};
int numsSize = 8;

int main(){
   int i, j, n, m, maxnum;
   int flag = 0;
   n = numsSize;
   int arr[n];
   int sum = 0;

   maxnum = 0;
   for( i=0; i<numsSize; i++ ){
        if( nums[i] == 0 )
            arr[i] = -1;
        else if( nums[i] == 1 )
            arr[i] = 1;
        else
            arr[i] = 0;
   }
   for( i=0; i<numsSize; i++ ){
        for( j=i; j<numsSize; j++ ){
            if( arr[i] != 0 ){
                flag = 1;
            }
            m = j-i+1;
            sum += arr[j];
            if( sum==0 && flag==1 ){
                maxnum = maxnum > m ? maxnum : m;
            }
        }
        sum = 0;
   }
   return maxnum;
}
