/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSymmetric(struct TreeNode* root){
    /* 根节点为空，即对称 */
    if (root == NULL) {
        return true;
    }
    /* 创建队列，保存节点 */
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 10000);
    int head = 0, rear = 0;
    queue[rear++] = root->left;
    queue[rear++] = root->right;
    /* 迭代遍历二叉树 */
    while (head != rear) {
        int preRear = rear;
        struct TreeNode* left  = queue[--rear];
        struct TreeNode* right = queue[--rear];
        /* 若两者都为空，则当前节点的左右孩子匹配，继续 */
        if (!left && !right) {
            continue;
        }
        /* 有一个为空另一个不为空，或者两者都不为空但是节点值不相等 */
        if (!left || !right || left->val != right->val) {
            return false;
        }
        /* 到这里则表示当前两节点匹配，再添加当前节点的左右节点入队列 */
        queue[rear++] = left->left;
        queue[rear++] = right->right;
        queue[rear++] = left->right;
        queue[rear++] = right->left;
    }
    return true;
}

作者：zhangdengyu
链接：https://leetcode-cn.com/problems/symmetric-tree/solution/101-dui-cheng-er-cha-shu-by-dyzahng-rp54/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。