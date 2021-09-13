/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *p = headA;
    struct ListNode *q = headB;
    while(p!=q)
    {
        if(p)
            p = p->next;
        else
            p = headB;
        if(q)
            q = q->next;
        else
            q = headA;
    }
    return q;
}

