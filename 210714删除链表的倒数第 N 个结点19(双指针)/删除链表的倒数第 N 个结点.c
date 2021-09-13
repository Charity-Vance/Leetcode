/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode* fast = head;
    struct ListNode* slow = head;
    struct ListNode* curr = slow;
    int i;

    for( i=0; i<n; i++ ){
        fast = fast->next;
    }
    /*fast指向空，只要删除头结点*/
    if( fast == NULL ){
        slow = head->next;
        return slow;
    }
    fast = fast->next;
    while( fast != NULL ){
        fast = fast->next;
        slow = slow->next;
    }
    /*fast指针已经指向末尾*/
    slow->next = slow->next->next;

    return curr;
}