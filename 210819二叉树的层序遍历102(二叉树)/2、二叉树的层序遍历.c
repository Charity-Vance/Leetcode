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
int max_depth;
int dfs( int** ans, struct TreeNode* root, int* res, int depth ){
    if( root == NULL )
        return;
    ans[depth][res[depth]++] = root->val;

    max_depth = max_depth>depth?max_depth:depth;

    dfs( ans, root->left, res, depth+1 );
    dfs( ans, root->right, res, depth+1 );

}
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int i, max_depth;
    int** ans = (int *)malloc(sizeof(int *) * 100 );
    int* res = (int )malloc(sizeof(int ) * 100 );
    for( i=0; i<100; i++ ){
        ans[i] = (int)malloc(sizeof(int ) * 100);
        res[i] = 0;
    }

    max_depth = 0;
    dfs( ans, root, res, 0 );

    *returnSize = max_depth;
    **returnColumnSizes = *res;
    return ans;
}