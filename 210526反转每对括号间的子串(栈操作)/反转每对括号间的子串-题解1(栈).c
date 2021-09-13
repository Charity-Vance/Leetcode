void reverse(char* str, int strSize) {
    for (int j = 0; j < strSize / 2; j++) {
        char tmp = str[j];
        str[j] = str[strSize - j - 1], str[strSize - j - 1] = tmp;
    }
}

char* reverseParentheses(char* s) {
    int n = strlen(s);
    char* stk[n];
    int top = 0;
    char* str = malloc(sizeof(char) * (n + 1));
    str[0] = '\0';
    int strSize = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stk[top] = malloc(sizeof(char) * (strSize + 1));
            memcpy(stk[top], str, sizeof(char) * (strSize + 1));
            top++;
            str[0] = '\0';
            strSize = 0;
        } else if (s[i] == ')') {
            reverse(str, strSize);
            int len = strlen(stk[top - 1]);
            for (int j = strSize; j >= 0; j--) {
                str[j + len] = str[j];
            }
            memcpy(str, stk[top - 1], sizeof(char) * len);
            strSize += len;
            top--;
        } else {
            str[strSize++] = s[i];
            str[strSize] = '\0';
        }
    }
    return str;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/reverse-substrings-between-each-pair-of-parentheses/solution/fan-zhuan-mei-dui-gua-hao-jian-de-zi-chu-gwpv/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。