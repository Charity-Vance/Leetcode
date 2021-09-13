/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void dfs(struct TreeNode* T, int* root, int* len) {
    //如果当前结点存在
    if (T) 
    {
        if( !(T->left) && !(T->right) )     /*左右子节点都不存在*/
        {
            root[(*len)++] = T->val;
        }
        dfs(T->left, root, len);
        dfs(T->right, root, len);
    }
}

bool leafSimilar(struct TreeNode* BiTNode1, struct TreeNode* BiTNode2){
    int BiTNode1_len=0;
    int BiTNode2_len=0;
    int i;
    int* root1 = (int* )malloc(sizeof(int) * 100);      /*应该预分配多大的内存*/
    int* root2 = (int* )malloc(sizeof(int) * 100);

    root1[0] = 0;
    root2[0] = 1;

    dfs(BiTNode1, root1, &BiTNode1_len);
    dfs(BiTNode2, root2, &BiTNode2_len);
    if( BiTNode1_len != BiTNode2_len )
    {
        return false;
    }
    for( i=0; i<BiTNode1_len; i++ )
    {
        if( root1[i] != root2[i] )
            return false;
    }
    return true;
}