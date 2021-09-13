/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {

    int flag = 0;
    struct ListNode *head1,*head2;
    if( headA == NULL || headB == NULL ){
        return NULL;
    }
    head1 = headA;
    head2 = headB;
    while( head1 != head2 ){
        if( head1 == head2 ){
            return head1;
        }
        if( head1 == NULL ){
            head1 = headB;
            flag = 1;
        }
        if( head2 == NULL ){
            head2 = headA;
        }
        head1 = head1->next;
        head2 = head2->next;
        if( flag && head1 == NULL ){
            return head1;
        }
    }
    return head1;
}