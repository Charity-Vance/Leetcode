/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int func(struct TreeNode* root,int *max){
    if(root==NULL){
        return 0;
    }
    int left=func(root->left,max)+1;
    int right=func(root->right,max)+1;
    if((*max)<(left+right)) *max=right+left;
    return left>right?left:right;
}
int diameterOfBinaryTree(struct TreeNode* root){
    if(root==NULL){
        return 0;
    }
    if(root->left==NULL&&root->right==NULL){
        return 0; 
    }
    int max=0;
    func(root,&max);
    return max-2;
}

