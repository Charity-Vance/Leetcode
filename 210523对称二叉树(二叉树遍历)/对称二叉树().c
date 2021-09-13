/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void inorder(struct TreeNode* T1, struct TreeNode* T2, int* res ) {
    if( !T1 || !T2 ){
        if( !(!T1 && !T2) ){
            *res = 1;
        }
        return;
    }
    if( T1->val != T2->val ){
        *res = 1;
    }
    inorder( T1->left, T2->right, res );
    // res[(*resSize)++] = root->val;
    inorder( T1->left, T2->right, res );
}

bool isSymmetric(struct TreeNode* root){
    int res = 0;     //默认为对称
    // int* res = malloc(sizeof(int) * 501);
    if( !root ){
        return false;
    }
    inorder( root->left, root->right, &res );

    return res;
}