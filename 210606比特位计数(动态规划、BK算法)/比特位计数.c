/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int* countBits(int n, int* returnSize){
   int flag = 0;
   int i, data_num, idata;
   int *res = (int*)malloc(sizeof(int) * (n + 1));

   data_num = 0;
   memset( res,0,sizeof(res) );//赋数组初值全为0；
   for( i=0; i<n+1; i++ ){
       idata = i;
       while( idata != 0 ){
           if( idata & 0x01 ){
               data_num++;
           }
           // data_num += idata&1;
           idata = idata>>1;         
       }
       res[i] = data_num;
       data_num = 0;
   }
   *returnSize = n+1;
   return res;
}

/*testcode*/
#include<stdio.h>
#include <string.h>

int n = 5;

int main(void){
    int flag = 0;
    int i, data_num, idata;
    int res[n+1];

    data_num = 0;
    memset( res,0,sizeof(res) );//赋数组初值全为0；
    for( i=0; i<n+1; i++ ){
        idata = i;
        while( idata != 0 ){
            if( idata & 0x01 ){
                data_num++;
            }
            idata = idata>>1;         
        }
        res[i] = data_num;
        data_num = 0;
    }
//    return res;
	return 0; 
}
