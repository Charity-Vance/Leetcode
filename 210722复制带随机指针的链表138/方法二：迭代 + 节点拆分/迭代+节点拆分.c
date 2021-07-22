struct Node* copyRandomList(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }
    for (struct Node* node = head; node != NULL; node = node->next->next) {
        struct Node* nodeNew = malloc(sizeof(struct Node));
        nodeNew->val = node->val;
        nodeNew->next = node->next;
        node->next = nodeNew;
    }
    for (struct Node* node = head; node != NULL; node = node->next->next) {
        struct Node* nodeNew = node->next;
        nodeNew->random = (node->random != NULL) ? node->random->next : NULL;
    }
    struct Node* headNew = head->next;
    for (struct Node* node = head; node != NULL; node = node->next) {
        struct Node* nodeNew = node->next;
        node->next = node->next->next;
        nodeNew->next = (nodeNew->next != NULL) ? nodeNew->next->next : NULL;
    }
    return headNew;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/copy-list-with-random-pointer/solution/fu-zhi-dai-sui-ji-zhi-zhen-de-lian-biao-rblsf/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
