/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct HashTable {
    char* key;
    int val;
    UT_hash_handle hh;
};

struct HashTable* cnt;

int queryVal(struct HashTable* hashTable, char* ikey) {
    struct HashTable* tmp;
    HASH_FIND_STR(hashTable, ikey, tmp);
    return tmp == NULL ? 0 : tmp->val;
}

int cmp(char** a, char** b) {
    int valA = queryVal(cnt, *a), valB = queryVal(cnt, *b);
    if (valA != valB) {
        return valB - valA;
    }
    int lenA = strlen(*a), lenB = strlen(*b);
    int len = fmin(lenA, lenB);
    for (int i = 0; i < len; i++) {
        if ((*a)[i] != (*b)[i]) {
            return (*a)[i] - (*b)[i];
        }
    }
    return lenA - lenB;
}

char** topKFrequent(char** words, int wordsSize, int k, int* returnSize) {
    cnt = NULL;
    for (int i = 0; i < wordsSize; i++) {
        struct HashTable* tmp;
        HASH_FIND_STR(cnt, words[i], tmp);
        if (tmp == NULL) {
            struct HashTable* tmp = malloc(sizeof(struct HashTable));
            tmp->key = words[i];
            tmp->val = 1;
            HASH_ADD_KEYPTR(hh, cnt, tmp->key, strlen(tmp->key), tmp);
        } else {
            tmp->val++;
        }
    }
    char** ret = malloc(sizeof(char*) * HASH_COUNT(cnt));
    *returnSize = 0;

    struct HashTable *iter, *tmp;
    HASH_ITER(hh, cnt, iter, tmp) {
        ret[(*returnSize)++] = iter->key;
    }

    qsort(ret, *returnSize, sizeof(char*), cmp);
    *returnSize = k;
    return ret;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/top-k-frequent-words/solution/qian-kge-gao-pin-dan-ci-by-leetcode-solu-3qk0/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。