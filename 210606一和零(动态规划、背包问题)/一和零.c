int findMaxForm(char ** strs, int strsSize, int m, int n){
    int buf_1[600] = {0};
    int buf_0[600] = {0};
    int i, j, len, sum_1, sum_0;

    len = strsSize;
    sum_0 = 0;
    sum_1 = 0;
    for( i=0,j=0; i<len; i++ ){
        while( *(*(str+i)+j) != '\0' ){
            if( *(*(str+i)+j) == 1 )
                buf_1[i]++;
            else
                buf_0[i]++;
    }
}