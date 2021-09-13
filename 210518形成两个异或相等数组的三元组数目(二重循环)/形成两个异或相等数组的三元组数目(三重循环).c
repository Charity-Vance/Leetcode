int countTriplets(int* arr, int arrSize){
    int n = arrSize+1;
    int XORSum[n];
    int i,j,k;
    int ans = 0;

    XORSum[0] = 0;
    for( i=0; i<n-1; i++ ){
        XORSum[i+1] = XORSum[i] ^ arr[i];
    }
    for( i=0; i<arrSize; i++ ){
        for( j=i+1; j<arrSize; j++ ){
            for( k=j; k<arrSize; k++ ){
                if( XORSum[i] == XORSum[k+1] )
                    ans++;
            }
        }
    }
    return ans;
}