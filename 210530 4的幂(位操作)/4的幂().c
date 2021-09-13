bool isPowerOfFour(int n){
    int i;
    for( i=0; i<30; i=i+2 ){
        if( 1 << i == n)
            return true;
    }
    return
        false;
}