#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int heightSize = 9;
int height[9] = {1,8,6,2,5,4,8,3,7};

int cmp(const void *a,const void *b)
{
    int *c = (int *)(a+1);
    int *d = (int *)(b+1);
    if(*c < *d)
        return -1;
    return 1;
}

int Volume( int x1, int x2, int h1, int h2 ){
    int width, height;
    if( x1 > x2 )
        width = x1 - x2;
    else
        width = x2 - x1;
    height = h1<h2?h1:h2;
    return height*width;
}

int main(void){

    int i, j, N, V, V_max;
    int wid, h, x1, x2;

    if( heightSize == 2 ){
        return height[0]*height[1];
    }

    N = heightSize;
    // int sort[30000][2] = {0};//sort[i][0]所在的位置，sort[i][1]高度
    /*二维数组的定义:利用二级指针申请一个二维数组*/
    // int **sort;
    // sort=(int**)malloc(sizeof(int*)*9);  
    // for(i=0;i<N;i++)  
    // sort[i]=(int*)malloc(sizeof(int)*2); 
    /*二维数组的定义:用数组指针形式申请一个二维数组*/
    int (*sort)[2]=(int(*)[2])malloc(sizeof(int)*N*2);
    /*二维数组的定义:用一个单独的一维数组来模拟二维数组*/
    // int *sort;
    // sort=(int *)malloc(N*2*sizeof(int));   //申请内存空间
    // //sort[i*N+j]//等价于sort[i][j]

    for( i=0; i<9; i++ ){
        sort[i][0] = i;
        sort[i][1] = height[i];
    }
    qsort( sort, N, sizeof(sort[0]), cmp );

    x1 = N-2;
    x2 = N-1;
    V_max = V = Volume( sort[x1][0], sort[x2][0], sort[x1][1], sort[x2][1] );
    for( i=N-3; i>=0; i-- ){
        V = Volume( sort[x1][0], sort[i][0], sort[x1][1], sort[i][1] );
        if( V > V_max ){
            V_max = V;
            x2 = i;
        }
        V = Volume( sort[i][0], sort[x2][0], sort[i][1], sort[x2][1] );
        if( V > V_max ){
            V_max = V;
            x1 = i;
        }
    }
    return V_max;
}

