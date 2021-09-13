void swap(char* a, char* b) {
    char tmp = *a;
    *a = *b, *b = tmp;
}

void reverse(char* l, char* r) {
    while (l < r) {
        swap(l++, --r);
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

char* reverseStr(char* s, int k) {
    int n = strlen(s);
    for (int i = 0; i < n; i += 2 * k) {
        reverse(&s[i], &s[min(i + k, n)]);
    }
    return s;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/reverse-string-ii/solution/fan-zhuan-zi-fu-chuan-ii-by-leetcode-sol-ua7s/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。