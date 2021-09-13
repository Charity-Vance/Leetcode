struct HashTable {
    int key, val;
    UT_hash_handle hh;
};

int findMaxLength(int* nums, int numsSize) {
    int maxLength = 0;
    struct HashTable* hashTable = NULL;
    struct HashTable* tmp = malloc(sizeof(struct HashTable));
    tmp->key = 0, tmp->val = -1;
    HASH_ADD_INT(hashTable, key, tmp);
    int counter = 0;
    int n = numsSize;
    for (int i = 0; i < n; i++) {
        int num = nums[i];
        if (num == 1) {
            counter++;
        } else {
            counter--;
        }
        HASH_FIND_INT(hashTable, &counter, tmp);
        if (tmp != NULL) {
            int prevIndex = tmp->val;
            maxLength = fmax(maxLength, i - prevIndex);
        } else {
            tmp = malloc(sizeof(struct HashTable));
            tmp->key = counter, tmp->val = i;
            HASH_ADD_INT(hashTable, key, tmp);
        }
    }
    return maxLength;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/contiguous-array/solution/lian-xu-shu-zu-by-leetcode-solution-mvnm/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。