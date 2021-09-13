/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    if( (preorder==NULL) || (inorder==NULL) || (preorderSize!=inorderSize) )
        return NULL;

    struct TreeNode* curRoot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
}