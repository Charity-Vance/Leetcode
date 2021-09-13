    char* longestPalindrome(char* s) 
    {
        if (strlen(s) < 1)
        {
            return "";
        }
        int start = 0, end = 0;
        for (int i = 0; i < strlen(s); i++)
        {
            int len1 = expandAroundCenter(s, i, i);//一个元素为中心
            int len2 = expandAroundCenter(s, i, i + 1);//两个元素为中心
            int len = max(len1, len2);
            if (len > end - start)
            {
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }
        return s.substr(start, end - start + 1);
    }

    int expandAroundCenter(char* s, int left, int right)
    {
        int L = left, R = right;
        while (L >= 0 && R < strlen(s) && s[L] == s[R])
        {// 计算以left和right为中心的回文串长度
            L--;
            R++;
        }
        return R - L - 1;
    }
作者：bian-bian-xiong
链接：https://leetcode-cn.com/problems/longest-palindromic-substring/solution/5-zui-chang-hui-wen-zi-chuan-cc-by-bian-bian-xiong/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。