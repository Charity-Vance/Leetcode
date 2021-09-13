int hammingDistance(int x, int y){
    int i, res = 0;
    int x1, y1;

    for( i=0; i<32; i++ ){
        if( x&0x01 ^ y&0x01 )
            res++;
        x = x >> 1;
        y = y >> 1;
    }
    return res;
}