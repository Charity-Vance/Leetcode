/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool compare(struct TreeNode* left, struct TreeNode* right) {
    if ((left == NULL && right != NULL)
        || (left != NULL && right == NULL)) {   /* 单个节点为空，匹配失败 */
            return false;
    } else if (left == NULL && right == NULL) { /* 都为空，匹配成功 */
        return true;
    } else if (left->val != right->val) {   /* 都不为空，节点值不相同，匹配失败 */
        return false;
    }
    /* 运行到此表示当前节点不为空，且节点值相等，开始递归 */
    bool outside    = compare(left->left, right->right);
    bool inside     = compare(left->right, right->left);
    /* 返回递归结果 */
    return outside && inside;
}

bool isSymmetric(struct TreeNode* root){
    /* 根节点为空，则对称 */
    if (root == NULL) {
        return true;
    }
    /* 递归判断 */
    return compare(root->left, root->right);
}
