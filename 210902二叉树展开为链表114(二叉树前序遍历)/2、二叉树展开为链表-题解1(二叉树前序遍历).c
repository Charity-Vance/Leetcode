int num;

void flatten(struct TreeNode* root) {
    num = 0;
    struct TreeNode** tmp = (struct TreeNode**)malloc(0);
    preorderTraversal(root, &tmp);
    for (int i = 1; i < num; i++) {
        struct TreeNode *prev = tmp[i - 1], *curr = tmp[i];
        prev->left = NULL;
        prev->right = curr;
    }
    free(tmp);
}

void preorderTraversal(struct TreeNode* root, struct TreeNode*** tmp) {
    if (root != NULL) {
        num++;
        (*tmp) = (struct TreeNode**)realloc((*tmp), sizeof(struct TreeNode*) * num);
        (*tmp)[num - 1] = root;
        preorderTraversal(root->left, tmp);
        preorderTraversal(root->right, tmp);
    }
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/solution/er-cha-shu-zhan-kai-wei-lian-biao-by-leetcode-solu/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。