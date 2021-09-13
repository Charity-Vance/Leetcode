/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int ROOTData[2001] = {0};
int h_max = 0;
int height = 0;

void dfs( struct TreeNode* root ){
    if( root == NULL )
        return;
    ROOTData[h_max++] = root->val;
    dfs( root->left );
    dfs( root->right );
}

void dfs1( struct TreeNode* root ){
    if( height >= h_max )
        return;
    if( root == NULL ){
        root = (struct TreeNode*)malloc(sizeof(struct TreeNode*));
    }
    root->val = ROOTData[height++];
    root->left = NULL;
    dfs1( root->right );
}

void flatten(struct TreeNode* root){
    if( root == NULL )
        return NULL;
    dfs( root );
    dfs1( root );
}