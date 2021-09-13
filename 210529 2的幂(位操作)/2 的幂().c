bool isPowerOfTwo(int n){
    int i;
    for( i=0; i<30; i++ ){
        if( 1 << i == n)
            return true;
    }
    return
        false;
}