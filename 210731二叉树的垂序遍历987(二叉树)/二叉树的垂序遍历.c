/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define NODESIZE 1000
#define COWSSIZE 500
#define ARRRAYSIZE 3

struct NodeArray {
    int row;  //节点所在的行数
    int col;  //节点所在的列数
    int val;  //节点的值
};

int Node_rows = 0;  //全局变量，遍历时节点所在行数
int Node_cols = 0;  //全局变量，遍历时节点所在列数
int firstNode_flag = 0;  //最左侧节点标志，找到时置1,使用后置2

/*结构体比较，先比较列数，再比较节点值*/
int ArrayCmp( const void *a, const void *b ){
    struct NodeArray tmp1 = *(struct NodeArray *)a;
    struct NodeArray tmp2 = *(struct NodeArray *)b;
    if( tmp1.row != tmp2.row ){
        return tmp1.row - tmp2.row;
    }
    return tmp1.val - tmp2.val;
}

/*遍历二叉树，将节点的行数、列数、值传递给ans*/
void dfs(struct TreeNode* root, int* returnSize, int** returnColumnSizes, struct NodeArray *ans ){
    if( (root == NULL) && (firstNode_flag == 0) ){ //该节点的父节点为最左节点
        firstNode_flag = 1;
        return;
    }
    if( firstNode_flag == 2 ){
        ans[*returnSize] = (int *)malloc(sizeof(int) * ARRRAYSIZE);
        ans[*returnSize].row = Node_rows;
        ans[*returnSize].col = Node_cols;
        ans[*returnSize].val = root->val;
        (*returnSize)++;
    }
    Node_rows++;
    Node_cols--;
    dfs( root->left, returnSize, returnColumnSizes, ans );  //遍历左子树
    Node_cols++;
    if( firstNode_flag == 1 ){//该节点为最左节点
        ans[*returnSize] = (int *)malloc(sizeof(int) * ARRRAYSIZE);
        ans[*returnSize].row = Node_rows;
        ans[*returnSize].col = Node_cols;
        ans[*returnSize].val = root->val;
        (*returnSize)++;
        firstNode_flag = 2; //置标志位2，可以开始对ans赋值
    }
    Node_cols++;
    dfs( root->right, returnSize, returnColumnSizes, ans );  //遍历右子树
    Node_cols--;
    Node_rows--;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** verticalTraversal(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    struct NodeArray *ans = (struct NodeArray *)malloc(sizeof(struct NodeArray) * NODESIZE);
    *returnColumnSizes = (int *)malloc(sizeof(int) * COWSSIZE);

    dfs( root, returnSize, returnColumnSizes, ans );  //开始遍历二叉树
    qsort( ans, *returnSize, sizeof(ans[0]), ArrayCmp );

}