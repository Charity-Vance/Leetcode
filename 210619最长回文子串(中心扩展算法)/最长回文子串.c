char * longestPalindrome(char * s){
    int i, j, k, n, maxlen, len, start;
    char *str;

    n = strlen(s);
    maxlen = 1;
    len = 1;
    if( n == 0 )
        return 0;
    str[0] = s[0];
    str[1] = '\0';
    for( i=1; i<n; i++ ){
        j = 1;
        while( i-j>=0 && i+j<=n ){//以i为中心的回文字符串有多少
            if( s[i-j] != s[i+j] )
                break;
            j++;
        }
        if( j > maxlen ){//找到当前最长回文字符串
            maxlen = j;
            len = 2*j-1;
            start = i-j;
        }
    }
    str = malloc(maxlen + 1);
    strncpy(str, s + start, maxlen);
    str[maxlen] = '\0';
    return str;
}

/*testcode*/
#include<stdio.h>
#include <string.h> 

char s[] = "abcbadd";
void main(){
    int i, j, k, n, maxlen, len;
    char str[1000];

    n = strlen(s);
    maxlen = 1;
    len = 1;
    if( n == 0 )
    //    return 0;
    str[0] = s[0];
    str[1] = '\0';
    for( i=1; i<n; i++ ){
        j = 1;
        while( i-j>=0 && i+j<=n ){//以i为中心的回文字符串有多少
            if( s[i-j] != s[i+j] )
                break;
            j++;
        }
        if( j > maxlen ){//找到当前最长回文字符串
            maxlen = j;
            len = 2*j-1;
            for( k=0; k<len; k++ ){
                str[k] = s[i-j+k];
            }
            str[k] = '\0';
        }
    }
    //return str;
}
