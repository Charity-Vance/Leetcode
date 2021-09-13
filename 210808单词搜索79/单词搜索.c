int chess[6][6] = {0};
int sucess_flag = 0;
int chlen = 0;

int dfs( char** board, int m, int n, int x, int y, char* word, int times ){
    char ch;

    if( sucess_flag == 1 )
        return;
    if( times >= chlen-1 ){
        sucess_flag = 1;
        return;
    }
    ch = word[times];
    //单元格的上方
    if( (y > 0) && (board[x][y-1] == ch) && (chess[x][y-1] == 0) ){
        chess[x][y-1] = 1;
        dfs( board, m, n, x, y-1, word, times+1 );
        chess[x][y-1] = 0;
    }
    //单元格的左侧
    if( (x > 0) && (board[x-1][y] == ch) && (chess[x-1][y] == 0) ){
        chess[x-1][y] = 1;
        dfs( board, m, n, x-1, y, word, times+1 );
        chess[x-1][y] = 0;
    }
    //单元格的下方
    if( (y < n-1) && (board[x][y+1] == ch) && (chess[x][y+1] == 0) ){
        chess[x][y+1] = 1;
        dfs( board, m, n, x, y+1, word, times+1 );
        chess[x][y+1] = 0;
    }
    //单元格的右侧
    if( (x < m-1) && (board[x+1][y] == ch) && (chess[x+1][y] == 0) ){
        chess[x+1][y] = 1;
        dfs( board, m, n, x+1, y, word, times+1 );
        chess[x+1][y] = 0;
    }
}
bool exist(char** board, int boardSize, int* boardColSize, char * word){
    int i, j, m, n;

    m = boardSize;
    n = boardColSize[0];
    for( i=0; i<m; i++ ){
        for( j=0; j<n; j++ ){
            chess[i][j] = 0;
        }
    }
    chlen = strlen(word);
    for( i=0; i<m; i++ ){
        for( j=0; j<n; j++ ){
            if( board[i][j] == word[0] )
                dfs( board, m, n, i, j, word, 0 );
        }
    }
    if( sucess_flag == 1 )
        return true;
    else
        return false;
}