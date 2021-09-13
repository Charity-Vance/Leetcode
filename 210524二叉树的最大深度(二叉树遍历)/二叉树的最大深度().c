/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int depth = 0;
int max_depth = 1;

void inorder( struct TreeNode* root ) {
    if (!root) {
        return;
    }
    depth++;
    max_depth = depth > max_depth ? depth : max_depth;
    inorder( root->left );
    inorder( root->right );
    depth--;
}

int maxDepth(struct TreeNode* root){

    inorder( root );

    return max_depth;
}