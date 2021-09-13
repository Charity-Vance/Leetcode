int kthLargestValue(int** matrix, int matrixSize, int* matrixColSize, int k){
    int m = matrixSize, n = matrixColSize[0];
    int XORSum[m+1][n+1];
    int i, j, temp;
    int size = (m+1)*(n+1);

    // memset( XORSum, 0, (m+1)*(n+1) );
    memset(XORSum, 0, sizeof(XORSum));
     for( i=0; i<size; i++ ){
        *(*XORSum+i) = 0x00;
    }
    for( i=0; i<m; i++ ){
        for( j=0; j<n; j++ ){
            XORSum[i+1][j+1] = matrix[i][j] ^ XORSum[i+1][j] ^ XORSum[i][j+1] ^ XORSum[i][j];
        }
    }
    for ( i = 0; i<size - 1; i++)
        for ( j = 0; j < size - i - 1; j++)
        {
            if ( *(*XORSum+j) < *(*XORSum+j+1) ) {
                temp = *(*XORSum+j); *(*XORSum+j) = *(*XORSum+j+1); *(*XORSum+j+1) = temp;
            }
        }    
    return *(*XORSum+k-1);
}
/**以下为调试信息**/
int main(){
    int m = 2, n = 2;
    int XORSum[m+1][n+1];
    //int arr[m*n];
    int i, j, temp, k=1;
    int size = (m+1)*(n+1);
    int matrix[2][2] = { {5,2}, {1,6} };
    // int a[5][3] = { {80,75,92}, {61,65,71}, {59,63,70}, {85,87,90}, {76,77,85} };
    // int b[5][3]={80, 75, 92, 61, 65, 71, 59, 63, 70, 85, 87, 90, 76, 77, 85};

    memset( XORSum, 1, 9 );
    memset(XORSum, 0, sizeof(XORSum));
    for( i=0; i<size; i++ ){
        *(*XORSum+i) = 0x00;
    }
    for( i=0; i<m; i++ ){
        for( j=0; j<n; j++ ){
            XORSum[i+1][j+1] = matrix[i][j] ^ XORSum[i+1][j] ^ XORSum[i][j+1] ^ XORSum[i][j];
        }
    }
    // memset( arr, 0, m*n );
    // for( i=0; i<(m+1)*(n+1)-1; i++ ){
    //     for( j=0; j<n; j++ ){
    //         if( *(*XORSum+m*i+j) < *(*XORSum+m*i+j+1) ){
    //             temp = *(*XORSum+m*i+j);
    //             *(*XORSum+m*i+j) = *(*XORSum+m*i+j+1);
    //             *(*XORSum+m*i+j) = temp;
    //         }
    //     }
    // }
    for ( i = 0; i<size - 1; i++)
        for ( j = 0; j < size - i - 1; j++)
        {
            if ( *(*XORSum+j) < *(*XORSum+j+1) ) {
                temp = *(*XORSum+j); *(*XORSum+j) = *(*XORSum+j+1); *(*XORSum+j+1) = temp;
            }
        }    
    printf("%d\n", *(*XORSum+k-1));
    return *(*XORSum+k-1);
    // return *(*a+6);  该值为59
}
