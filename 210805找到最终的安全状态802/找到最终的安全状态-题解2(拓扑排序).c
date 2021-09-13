int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize) {
    int n = graphSize;
    int* rg[n];
    int rgCol[n];
    memset(rgCol, 0, sizeof(rgCol));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graphColSize[i]; j++) {
            rgCol[graph[i][j]]++;
        }
    }
    for (int i = 0; i < n; i++) {
        rg[i] = malloc(sizeof(int) * rgCol[i]);
        rgCol[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graphColSize[i]; j++) {
            rg[graph[i][j]][rgCol[graph[i][j]]++] = i;
        }
    }
    int inDeg[n];
    memcpy(inDeg, graphColSize, sizeof(int) * n);

    int que[10000];
    int left = 0, right = 0;
    for (int i = 0; i < n; ++i) {
        if (inDeg[i] == 0) {
            que[right++] = i;
        }
    }
    while (left < right) {
        int y = que[left++];
        for (int i = 0; i < rgCol[y]; i++){
            if (--inDeg[rg[y][i]] == 0) {
                que[right++] = rg[y][i];
            }
        }
    }

    int *ans = malloc(sizeof(int) * n);
    *returnSize = 0;
    for (int i = 0; i < n; ++i) {
        if (inDeg[i] == 0) {
            ans[(*returnSize)++] = i;
        }
    }
    return ans;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/find-eventual-safe-states/solution/zhao-dao-zui-zhong-de-an-quan-zhuang-tai-yzfz/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。