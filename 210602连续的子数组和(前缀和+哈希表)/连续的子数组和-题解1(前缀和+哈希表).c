struct HashTable {
    int key, val;
    UT_hash_handle hh;
};

bool checkSubarraySum(int* nums, int numsSize, int k) {
    int m = numsSize;
    if (m < 2) {
        return false;
    }
    struct HashTable* hashTable = NULL;
    struct HashTable* tmp = malloc(sizeof(struct HashTable));
    tmp->key = 0, tmp->val = -1;
    HASH_ADD_INT(hashTable, key, tmp);
    int remainder = 0;
    for (int i = 0; i < m; i++) {
        remainder = (remainder + nums[i]) % k;
        HASH_FIND_INT(hashTable, &remainder, tmp);
        if (tmp != NULL) {
            int prevIndex = tmp->val;
            if (i - prevIndex >= 2) {
                return true;
            }
        } else {
            tmp = malloc(sizeof(struct HashTable));
            tmp->key = remainder, tmp->val = i;
            HASH_ADD_INT(hashTable, key, tmp);
        }
    }
    return false;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/continuous-subarray-sum/solution/lian-xu-de-zi-shu-zu-he-by-leetcode-solu-rdzi/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。