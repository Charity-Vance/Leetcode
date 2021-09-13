int color[10000];

bool safe(int** graph, int graphSize, int* graphColSize, int x) {
    if (color[x] > 0) {
        return color[x] == 2;
    }
    color[x] = 1;
    for (int i = 0; i < graphColSize[x]; i++){
        if (!safe(graph, graphSize, graphColSize, graph[x][i])) {
            return false;
        }
    }
    color[x] = 2;
    return true;
}

int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize) {
    memset(color, 0, sizeof(int) * graphSize);
    int* ans = malloc(sizeof(int) * graphSize);
    *returnSize = 0;
    for (int i = 0; i < graphSize; ++i) {
        if (safe(graph, graphSize, graphColSize, i)) {
            ans[(*returnSize)++] = i;
        }
    }
    return ans;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/find-eventual-safe-states/solution/zhao-dao-zui-zhong-de-an-quan-zhuang-tai-yzfz/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。