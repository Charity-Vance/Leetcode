/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include<stdio.h>

#define arrlen 1
#define querieslen 4

int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, 
                int* queriesColSize, int* returnSize)
{
    int i,j,Li,Ri;
    int v_data;
    int *return_arr = (int *)malloc(sizeof(int *) * arrSize);

    for( i=0; i<queriesSize; i++ )
    {
        v_data = 0;
        Li = queries[i][0];
        Ri = queries[i][1];
//        Li = queries[i][0];Ri = queries[i][1];
        for( j=Li; j<= Ri; j++ )
        {
            v_data ^= arr[j];
        }
        return_arr[i] = v_data;
    }
    * returnSize = arrSize;
    return return_arr;
}

int main()
{
    int i,j,Li,Ri;
    int v_data;
    int *return_arr = (int *)malloc(sizeof(int *) * arrlen);
    int arr[arrlen] ={16};
    int queries[querieslen][2] = {{0,0},{0,0},{0,0}};

    for( i=0; i<querieslen; i++ )
    {
        v_data = 0;
        Li = queries[i][0];
        Ri = queries[i][1];
//        Li = queries[i][0];Ri = queries[i][1];
        for( j=Li; j<= Ri; j++ )
        {
            v_data ^= arr[j];
        }
        return_arr[i] = v_data;
    }
    //* returnSize = arrSize;
    return return_arr;
}
