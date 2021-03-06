char * longestPalindrome(char * s){
    int i=0,length=0,j=1,flag=1,flag1=1,max=1;
    //max为最长回文子串的长度，length为最长回文子串的首位置
    //用i对字符串s进行扫描 
    while(*(s+i+max/2)!='\0')//扫描结束条件
    {
        flag=1;j=0;
        //用本文所列第一种回文情况对位置(s+i)进行判断
        while((j<=i)&&(*(s+i+j+1)!='\0')&&flag)
        {
            if(*(s+i-j)==*(s+i+j+1)) j++;//若符合回文条件则继续比较下对字符
            else //若不符合回文条件则比较最大长度
            {
                if(2*j>max) //若本次查找即为最大长度，则更新数据
                {
                    length=i-j+1;//更新最长回文子串的首位置
                    max=2*j;//更新最大长度
                    flag1=2;
                }
                flag=0;
            }
            if((j>i)||(*(s+i+j+1)=='\0'))//若下对要比较的字符位置非法，则结束查找
            {
                if(2*j>max)//若本次查找即为最大长度，则更新数据
                {
                    length=i-j+1;//更新最长回文子串的首位置
                    max=2*j;//更新最大长度
                    flag1=2;
                }
                flag=0;
            }
        }
        flag=1;j=1;
        //用本文所列第二种回文情况对位置(s+i)进行判断
        while((j<=i)&&(*(s+i+j)!='\0')&&flag)
        {
            if(*(s+i-j)==*(s+i+j)) j++;//若符合回文条件则继续比较下对字符
            else//若不符合回文条件则比较最大长度
            {
                if(2*j-1>max)//若本次查找即为最大长度，则更新数据
                {
                    length=i-j+1;//更新最长回文子串的首位置
                    max=2*j-1;//更新最大长度
                    flag1=3;
                }
                flag=0;
            }
        if((j>i)||(*(s+i+j)=='\0'))//若下对要比较的字符位置非法，则结束查找
        {    
                if(2*j-1>max)//若本次查找即为最大长度，则更新数据
                {
                    length=i-j+1;//更新最长回文子串的首位置
                    max=2*j-1;//更新最大长度
                    flag1=3;
                }
                flag=0;
        }
        }

        i++;
    }
    if(flag1==2)//最长回文子串为本文所列第一种情况
    {
        s=s+length;
        *(s+max)='\0';
        return s;
    }
    if(flag1==3) //最长回文子串为本文所列第一种情况
    {
        s=s+length;
        *(s+max)='\0';
        return s;
    }
    *(s+1)='\0';//特殊情况，字符串为两个不相等的字符
    return s;
}
