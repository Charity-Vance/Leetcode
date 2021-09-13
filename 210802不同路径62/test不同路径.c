#include<stdio.h>

int route = 0;
int loc_x = 1;
int loc_y = 1;

int dfs( int x, int y, int m, int n ){
    if( x >= m && y >= n ){
        route++;
        return;
    }     
    else if( x >= m ){
        dfs( x, y+1, m ,n );
    }
    else if( y >= n ){
        dfs( x+1, y, m, n );
    }
    else{
        dfs( x, y+1, m, n );
        dfs( x+1, y, m, n );
    }
}

int main( ){
    //int x, y;  //x横向坐标，对应n；y对应纵向坐标，对应m；
//	int m = 3;
//	int n = 7;
	 
    dfs( 1, 1, 3, 2 );

    printf("%d", route);
}
