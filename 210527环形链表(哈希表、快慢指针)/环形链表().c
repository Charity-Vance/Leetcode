/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    struct ListNode *fastNode = head;
    struct ListNode *slowNode = head;

    if( head == NULL || head->next == NULL ){
        return false;
    }
    while( fastNode != NULL && slowNode != NULL ){
        if( fastNode == NULL || fastNode->next == NULL )    //需要判断快指针是否指向空
            return false;
        fastNode = fastNode->next->next;
        slowNode = slowNode->next;

        if( fastNode == slowNode )
            return true;
    }
    return false;
}