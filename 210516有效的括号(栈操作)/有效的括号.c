bool isValid(char * s){
    int top = 0, bottom = 0;
    char array[1000] = {0};
    int len = strlen(s);
    int i = 0;

    while( i<len ){
        switch( s[i] ) 
        case '(':
        case '[':
        case '{':{
            array[top++] = s[i];i++;            
        }break;
        case ')':{
            if( array[top--] != '(' )
                return false;
            i++;
        }break;
        case ']':{
            if( array[top--] != '[' )
                return false;
            i++;
        }break;
        case '}':{
            if( array[top--] != '{' )
                return false;
            i++;
        }break;
        default:
            return false;
        break;
    }
    return true;
}
