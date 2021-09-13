
int compareVersion(char * version1, char * version2){
    int n = strlen(version1), m = strlen(version2);
    int i = 0, j = 0;
    while (i < n || j < m) {
        int x = 0;
        for (; i < n && version1[i] != '.'; ++i) {
            x = x * 10 + version1[i] - '0';
       }
        ++i; // 跳过点号
        int y = 0;
        for (; j < m && version2[j] != '.'; ++j) {
            y = y * 10 + version2[j] - '0';
        }
        ++j; // 跳过点号
        if (x != y) {
            return x > y ? 1 : -1;
        }
    }
    return 0;
}