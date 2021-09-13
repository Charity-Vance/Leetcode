#include<stdio.h>
#include<string.h>

char* s = "abcdefg";
int k = 2;

int swap( char* s1, char* s2 ){
    char tmp;
    tmp = s1;
    s1 = s2;
    s2 = tmp;
}

int rever( char* s, int len ){
    int left = 0;
    int right = len;

    while( left < right ){
        swap( s+left, s+right );
    }
}

void main(){
    int n = strlen(s);
    int slow = 0;
    int fast = slow + k;

    while(fast<n){
        rever( s+slow, k );
        slow += 2*k;
        fast = slow + k;
    }
    
}
