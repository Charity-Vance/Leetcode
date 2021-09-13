/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


bool isPalindrome(struct ListNode* head){
    int dataval[5001] = {0};
    int i;
    int length = 0;

    struct ListNode* fast = head;
    struct ListNode* slow = head;

    while( fast != NULL ){
        dataval[length++] = slow->val;
        slow = slow->next;
        fast = fsat->next->next;
    }
    while( slow != NULL ){
        if( dataval[--length] != slow->val )
            return false;
        slow = slow->next;
    }
    return rure;
}