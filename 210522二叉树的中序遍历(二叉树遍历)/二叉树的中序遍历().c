/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void InOrder(struct TreeNode* root) {
    //如果当前结点存在
    if (T) {
        InOrder(T->left);//递归当前结点的左子树，进行线索化
        InOrder(T->right);//递归右子树进行线索化
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize){

}