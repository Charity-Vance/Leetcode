int route = 0;

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
int uniquePaths(int m, int n){
    //int x, y;  //x横向坐标，对应n；y对应纵向坐标，对应m；

    dfs( 0, 0, m, n );

    return route;
}
