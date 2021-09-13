const int HIGH_BIT = 30;

struct HashTable {
    int key;
    UT_hash_handle hh;
};
/*pre^k(x)表示xx从最高位第30个二进制位开始，到第k个二进制位为止的数*/
int findMaximumXOR(int* nums, int numsSize) {
    int x = 0;
    for (int k = HIGH_BIT; k >= 0; --k) {
        struct HashTable* hashTable = NULL;
        // 将所有的 pre^k(a_j) 放入哈希表中
        for (int i = 0; i < numsSize; i++) {
            // 如果只想保留从最高位开始到第 k 个二进制位为止的部分
            // 只需将其右移 k 位
            int x = nums[i] >> k;
            struct HashTable* tmp;
            HASH_FIND_INT(hashTable, &x, tmp);
            if (tmp == NULL) {
                tmp = malloc(sizeof(struct HashTable));
                tmp->key = x;
                HASH_ADD_INT(hashTable, key, tmp);
            }
        }

        // 目前 x 包含从最高位开始到第 k+1 个二进制位为止的部分
        // 我们将 x 的第 k 个二进制位置为 1，即为 x = x*2+1
        int x_next = x * 2 + 1;
        bool found = false;

        // 枚举 i
        for (int i = 0; i < numsSize; i++) {
            int x = x_next ^ (nums[i] >> k);
            struct HashTable* tmp;
            HASH_FIND_INT(hashTable, &x, tmp);
            if (tmp != NULL) {
                found = true;
                break;
            }
        }

        if (found) {
            x = x_next;
        } else {
            // 如果没有找到满足等式的 a_i 和 a_j，那么 x 的第 k 个二进制位只能为 0
            // 即为 x = x*2
            x = x_next - 1;
        }
    }
    return x;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/solution/shu-zu-zhong-liang-ge-shu-de-zui-da-yi-h-n9m9/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。