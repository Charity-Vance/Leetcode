bool fun(struct TreeNode* root, long low, long high) {
    if (root == NULL) return true;
    long num = root->val;
    if (num <= low || num >= high) return false;
    return fun(root->left, low, num) && fun(root->right, num, high);
}
bool isValidBST(struct TreeNode* root){
    return fun(root, LONG_MIN, LONG_MAX);
}
