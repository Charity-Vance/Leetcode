/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define MAX_NUM 1004
struct TreeS {
    int val;
    int x;
    int y;
};

int g_tempCnt = 0;

//比较列大小
int cmpX(const void* _a , const void* _b) //参数格式固定
{
    struct TreeS *a = *(struct TreeS **)_a;
    struct TreeS *b = *(struct TreeS **)_b;
    return a->x - b->x;    // 升序
}

//先比较行，再比较值
int cmpY(const void* _a , const void* _b) //参数格式固定
{
    struct TreeS *a = *(struct TreeS **)_a;
    struct TreeS *b = *(struct TreeS **)_b;
    int ret = b->y - a->y;
    if (ret == 0) {
        ret = a->val - b->val;
    }
    return ret;
    // return a->y - b->y;    // 升序
    // return b->y - a->y;    // 降序
}

//(char ** products, int productsSize, char * searchWord, int* returnSize, int** returnColumnSizes)
//qsort(products, productsSize, sizeof(char *), cmpFunc);
/*
for (i = 0; i < g_tempCnt; i++) {
    printf("%d ", tempT[i]->x);
}
printf("\n");
*/

int dfs(struct TreeNode* root, int x, int y, struct TreeS **tempT)
{
    tempT[g_tempCnt]->val = root->val;
    tempT[g_tempCnt]->x = x;
    tempT[g_tempCnt]->y = y;
    g_tempCnt++;

    if (root->left != NULL) {
        dfs(root->left, x - 1, y - 1, tempT);
    }
    if (root->right != NULL) {
        dfs(root->right, x + 1, y - 1, tempT);
    }
    return 0;
}

int** verticalTraversal(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int i;
    int j;
    struct TreeS **tempT = (struct TreeS **)malloc(MAX_NUM * sizeof(struct TreeS *));
    for (i = 0; i < MAX_NUM; i++) {
        tempT[i] = (struct TreeS *)malloc(sizeof(struct TreeS));
        memset(tempT[i], 0, sizeof(struct TreeS));
    }

    *returnSize = 0;
    int *columnSizes = (int *)malloc(MAX_NUM * sizeof(int));
    memset(columnSizes, 0, MAX_NUM * sizeof(int));

    g_tempCnt = 0;
    dfs(root, 0, 0, tempT);

    qsort(tempT, g_tempCnt, sizeof(struct TreeS *), cmpX);
    i = 0;
    j = 0;
    while (1) {
        j++;
        if (j >= g_tempCnt) {
            break;
        }
        if (tempT[j]->x == tempT[i]->x) {
            continue;
        }
        if (j - i != 1) {
            qsort(&(tempT[i]), j - i, sizeof(struct TreeS *), cmpY);
        }
        columnSizes[*returnSize] = j - i;
        *returnSize = *returnSize + 1;

        i = j;
    }
    if (j - i != 1) {
        qsort(&(tempT[i]), j - i, sizeof(struct TreeS *), cmpY);
    }
    columnSizes[*returnSize] = j - i;
    *returnSize = *returnSize + 1;
    *returnColumnSizes = columnSizes;

    int cnt = 0;
    int **ans = (int **)malloc((*returnSize) * sizeof(int *));
    for (i = 0; i < *returnSize; i++) {
        ans[i] = (int *)malloc(columnSizes[i] * sizeof(int));
        for (j = 0; j < columnSizes[i]; j++) {
            ans[i][j] = tempT[cnt]->val;
            cnt++;
        }
    }

    return ans;
}
