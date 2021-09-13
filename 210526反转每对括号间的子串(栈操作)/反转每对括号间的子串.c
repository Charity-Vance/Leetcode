char * reverseParentheses(char * s){
    int i = 0, j, len;
    int str_left = 0, str_lright = 0;
    char str;

    whhile( s[i] != '\0' ){
        if( s[i] == '(' ){
            str_left = i;
        }
        if( s[i] == ')' ){
            s[str_left] = 0;
            s[i] = 0;
            len = ( i+1 - str_left )/2; 
            for( j=str_left; j<len; j++ ){
                str = s[j];
                s[j] = s[i-j+str_left];
                s[i-j+str_left] = str;
            }
            s[str_left] = 1;    //已翻转的置位
            s[i] = 1;
            i = 0;      //重新开始  
        }
        else{
            i++;
        }
    }
    len = i;
    for( i=0,j=0; i<len; i++ ){
        if( s[i] == 1 ){
            while( s[j] == 1 ){
                j++;
            }
            if( s[j] == '\0' ){
                s[i] = '\0';
                break;
            }
            s[i] = s[j];
            s[j] = 1;
        }
        else{
            j++;
        }
    }
    return s;
}