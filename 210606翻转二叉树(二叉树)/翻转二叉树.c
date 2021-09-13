/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void inorder( struct TreeNode* T1, struct TreeNode* T2 ){
    if( !T1 ){
        return NULL;
    }
    T2->val = T1->val;
    inorder( T1->left, T2->right );
    inorder( T1->right, T2->left );
}

struct TreeNode* invertTree(struct TreeNode* root){
    struct TreeNode* res;

    if( !root ){
        return root;
    }
    res = root;
    inorder( root, res );

    return res;
}