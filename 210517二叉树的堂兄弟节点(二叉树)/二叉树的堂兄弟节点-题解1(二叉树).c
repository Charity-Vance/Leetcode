/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
// x 的信息
int x_target;
struct TreeNode* x_parent;
int x_depth;
bool x_found;

// y 的信息
int y_target;
struct TreeNode* y_parent;
int y_depth;
bool y_found;

void dfs(struct TreeNode* node, int depth, struct TreeNode* parent) {
    if (!node) {
        return;
    }

    if (node->val == x_target) {
        x_parent = parent;
        x_depth = depth;
        x_found = true;
    } else if (node->val == y_target) {
        y_parent = parent;
        y_depth = depth;
        y_found = true;
    }

    // 如果两个节点都找到了，就可以提前退出遍历
    // 即使不提前退出，对最坏情况下的时间复杂度也不会有影响
    if (x_found && y_found) {
        return;
    }

    dfs(node->left, depth + 1, node);

    if (x_found && y_found) {
        return;
    }

    dfs(node->right, depth + 1, node);
}

bool isCousins(struct TreeNode* root, int x, int y) {
    x_target = x;
    y_target = y;
    x_found = false;
    y_found = false;
    dfs(root, 0, NULL);
    return x_depth == y_depth && x_parent != y_parent;
}
