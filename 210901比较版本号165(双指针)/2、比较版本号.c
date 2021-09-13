#define GREATER 1  //version1 > version2
#define LESS   -1  //version1 < version2
#define OTHER   0
#define NOT_Zero 0x68
#define IS_Zero  0
int CMP_Char( char *ch, int start, int len ){
    int i;
    for( i=start; i<len; i++ ){
        if( ch[i]!=0 && ch[i]!='.' )
            return NOT_Zero;
    }
    return IS_Zero;
}

int compareVersion(char * version1, char * version2){
    int x1 = 0;
    int x2 = 0;
    int len1 = strlen(version1);
    int len2 = strlen(version2);

    while( x1<len1 || x2<len2 ){
        while( x1<len1 && version1[x1]=='0' && version1[x1]!='.' ){  //按照修订号筛选
            x1++;
            if( x1<len1 &&version1[x1]=='.' ){
                x1--;break;
            }          
        }
        while( x2<len2 && version2[x2]=='0' && version2[x2]!='.' ){  //按照修订号筛选
            x2++;
            if( x2<len2 &&version2[x2]=='.' ){
                x2--;break;
            }                      
        }
        while( x1<len1 && x2<len2 && version1[x1]!='.' && version2[x2]!='.' ){
            if( version1[x1]=='.' || version1[x1]<version2[x2] )  //x1先到修订号
                return LESS;
            if( version2[x2]=='.' || version1[x1]>version2[x2] )  //x2先到修订号
                return GREATER;
            x1++;x2++;
        }
        x1++;x2++;  //跳过修订号
    }
    if( x1==len1 && x2<len2 ){  //判断version2后面的值是否为0
        if( CMP_Char( version2, x2, len2 ) )
            return LESS;
    }
    if( x2==len2 && x1<len1 ){  //判断version1后面的值是否为0
        if( CMP_Char( version1, x1, len1 ) )
            return GREATER;
    }
    return OTHER;
}