int climbStairs(int n){
    int odd = n/2;  //至多有odd个2
    int i, j, k;
    int res = 0;
    int sum = 1, div = 1;

    for( i=1; i<=odd; i++ ){
        // for( j=n-2*i,k=1; j<n-i+1; j++,k++ ){
        for( j=1,k=n-i; j<=i; j++,k-- ){
            sum *= k;
            div *= j;
        }
        res += sum/div;
        sum = 1; div = 1;
    }
    return res+1;
}
/*调试代码*/
int main(void){
    #define n 3
    int odd = n/2;  //至多有odd个2
    int i, j, k;
    int res = 0;
    int sum = 1, div = 1;

    for( i=1; i<=odd; i++ ){
        // for( j=n-2*i,k=1; j<n-i+1; j++,k++ ){
        for( j=1,k=n-i; j<=i; j++,k-- ){
            sum *= k;
            div *= j;
        }
        res += sum/div;
        sum = 1; div = 1;
    }
    return res+1;
}