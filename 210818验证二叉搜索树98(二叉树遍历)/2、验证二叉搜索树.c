/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int Judge_flag = 0;

void dfs( struct TreeNode* root, int data, int dir ){
    if( (root == NULL) || (Judge_flag == 1) )
        return;
    //左子树,数值小于data
    if( (dir == 0) && (root->val >= data) ){
        Judge_flag = 1;
        return;
    }
    //左子树,数值大于data
    if( (dir == 1) && (root->val <= data) ){
        Judge_flag = 1;
        return;
    }
    dfs( root->left, root->val, 0 );
    dfs( root->right, root->val, 1 );

}

bool isValidBST(struct TreeNode* root){

    if( root == NULL )
        return true;
    dfs( root->left, root->val, 0 );
    dfs( root->right, root->val, 1 );

    if( Judge_flag == 1 )
        return false;
    else
        return true;

}