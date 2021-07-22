struct HashTable {
    struct Node *key, *val;
    UT_hash_handle hh;
} * cachedNode;

struct Node* deepCopy(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }
    struct HashTable* tmp;
    HASH_FIND_PTR(cachedNode, &head, tmp);
    if (tmp == NULL) {
        struct Node* headNew = malloc(sizeof(struct Node));
        headNew->val = head->val;
        tmp = malloc(sizeof(struct HashTable));
        tmp->key = head, tmp->val = headNew;
        HASH_ADD_PTR(cachedNode, key, tmp);
        headNew->next = deepCopy(head->next);
        headNew->random = deepCopy(head->random);
    }
    return tmp->val;
}

struct Node* copyRandomList(struct Node* head) {
    cachedNode = NULL;
    return deepCopy(head);
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/copy-list-with-random-pointer/solution/fu-zhi-dai-sui-ji-zhi-zhen-de-lian-biao-rblsf/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
