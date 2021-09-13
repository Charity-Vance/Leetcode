/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int depth_x, father_x;
int depth_y, father_y;
int depth;

//中序遍历二叉树并进行线索化
void InOrder( struct TreeNode* T, int x, int y, struct TreeNode* parent ) 
{
    //如果当前结点存在
    if (T) {
        depth++;
        if( T->val == x ){
            depth_x = depth; 
            father_x = parent->val;
       }    
        if( T->val == y ){
            depth_y = depth;
            father_y = parent->val; 
        }        
        InOrder( T->left, x, y, T );
        InOrder( T->right, x, y, T );

        depth--;
    }
}
bool isCousins(struct TreeNode* root, int x, int y){
    depth = 1;

    InOrder( root, x, y, root );
    if( (depth_x == depth_y) && (father_x != father_y) )
        return true;
    else
        return false;
}