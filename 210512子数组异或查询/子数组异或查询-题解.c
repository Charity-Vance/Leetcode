/**
 * Note: The returned array must be malloced, assume caller calls free().
 先按顺序算出0到Ri异或的值，再算出0到Li异或的值，两者异或即可得到Li到Ri的值
 */
int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, 
                int* queriesColSize, int* returnSize) {
    int n = arrSize;
    int xors[n + 1];
    xors[0] = 0;
    for (int i = 0; i < n; i++) {
        xors[i + 1] = xors[i] ^ arr[i];
    }
    int m = queriesSize;
    int* ans = malloc(sizeof(int) * m);
    *returnSize = m;
    for (int i = 0; i < m; i++) {
        ans[i] = xors[queries[i][0]] ^ xors[queries[i][1] + 1];
    }
    return ans;
}

