#include<stdio.h>
#include <string.h>

int chess[6][6] = {0};
int sucess_flag = 0;
int chlen = 0;

char board[3][4] = { {'A','B','C','E'}, {'S','F','C','S'},{'A','D','E','E'}};
int boardSize = 3;
int boardColSize[1] = {4};
char word[] = "ABCCED";

int Chess_Output( int m, int n ){
	int i, j;
	
	for( i=0; i<m; i++ ){
		for( j=0; j<n; j++ ){
			if( chess[i][j] == 1 ){
				printf( "%c",board[i][j] );
			}
		}
	}
	printf("\n");
}
int dfs( int m, int n, int x, int y, char* word, int times ){
    char ch;

    if( sucess_flag == 1 )
        return;
    if( times >= chlen-1 ){
        sucess_flag = 1;
        return;
    }
    ch = word[times];
   
    Chess_Output( m, n );
    //单元格的上方
    if( (y > 0) && (board[x][y-1] == ch) && (chess[x][y-1] == 0) ){
        chess[x][y-1] = 1;
        dfs( m, n, x, y-1, word, times+1 );
        chess[x][y-1] = 0;
    }
    //单元格的左侧
    if( (x > 0) && (board[x-1][y] == ch) && (chess[x-1][y] == 0) ){
        chess[x-1][y] = 1;
        dfs( m, n, x-1, y, word, times+1 );
        chess[x-1][y] = 0;
    }
    //单元格的下方
    if( (y < n-1) && (board[x][y+1] == ch) && (chess[x][y+1] == 0) ){
        chess[x][y+1] = 1;
        dfs( m, n, x, y+1, word, times+1 );
        chess[x][y+1] = 0;
    }
    //单元格的右侧
    if( (x < m-1) && (board[x+1][y] == ch) && (chess[x+1][y] == 0) ){
        chess[x+1][y] = 1;
        dfs( m, n, x+1, y, word, times+1 );
        chess[x+1][y] = 0;
    }
}
//bool exist(char** board, int boardSize, int* boardColSize, char * word){
int main(){
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
            if( board[i][j] == word[0] ){
            	chess[i][j] = 1;
                dfs( m, n, i, j, word, 0 );
            	chess[i][j] = 0;
			}
        }
    }
    printf("%d",sucess_flag);
//    if( sucess_flag == 1 )
//        return 0;
//    else
//        return 1;
}
