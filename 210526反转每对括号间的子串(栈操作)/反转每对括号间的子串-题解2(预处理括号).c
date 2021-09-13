char* reverseParentheses(char* s) {
    int n = strlen(s);
    int pair[n];
    memset(pair, 0, sizeof(pair));
    int stk[n], top = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stk[top++] = i;
        } else if (s[i] == ')') {
            int j = stk[--top];
            pair[i] = j, pair[j] = i;
        }
    }
    char* ret = malloc(sizeof(char) * (n + 1));
    int retSize = 0;
    int index = 0, step = 1;
    while (index < n) {
        if (s[index] == '(' || s[index] == ')') {
            index = pair[index];
            step = -step;
        } else {
            ret[retSize++] = s[index];
        }
        index += step;
    }
    ret[retSize] = '\0';
    return ret;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/reverse-substrings-between-each-pair-of-parentheses/solution/fan-zhuan-mei-dui-gua-hao-jian-de-zi-chu-gwpv/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。