/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeElements(struct ListNode* head, int val){

    struct ListNode* p = head;
    struct ListNode* q = p;
    if( p == NULL ){
        return NULL;
    }
    while( q->val == val ){
        q = p->next;
        p = p->next;
        if( !p )
            break;
    }
    while( p != NULL ){
        if( p->next!=NULL && p->next->val==val ){
            p->next = p->next->next;
        }
        p = p->next;
    }
    return q;
}