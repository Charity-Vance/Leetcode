/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head = NULL, *tail = NULL;
    int v_data;

    if( !l1 && !l2 )    //两个都空
        return head;

    head = tail = malloc(sizeof(struct ListNode));
    tail->next = NULL;
    while( l1 || l2 ){
        if( l1 && !l2 ){        //l1不空，l2空
            v_data = l1->val;
            l1 = l1->next;
        }
        else if( l2 && !l1 ){   //l1空，l2不空
            v_data = l2->val;
            l2 = l2->next;
        }
        else if( l1 && l2 ){     //两个都不空
            if( l1->val <= l2->val ){
                v_data = l1->val;
                l1 = l1->next;
            }
            else{
                v_data = l2->val;
                l2 = l2->next;
            }
        }

        tail->val = v_data;
        tail->next = NULL;

        if( !l1 && !l2 )    //两个都空
            break;

        tail->val = v_data;
        tail->next = malloc(sizeof(struct ListNode));
        tail = tail->next;
        tail->next = NULL;
    }
    return head;
}