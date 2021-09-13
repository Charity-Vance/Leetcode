/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
/*定义新指针需要指向NULL*/

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    int carry = 0;  //进位数
    struct ListNode *head = NULL,*tail = NULL;
    int n1,n2,sum;

    head = tail = malloc(sizeof(struct ListNode));
    while( l1 || l2 )
    {
        n1 = l1 ? l1->val : 0;
        n2 = l2 ? l2->val : 0;
        sum = n1 + n2 + carry;
        carry = sum / 10;
        tail->val = sum % 10;
        tail->next = NULL;
        if( l1 )
        {
            l1 = l1->next;
        }
        if( l2 )
        {
            l2 = l2->next;
        }
        if( !l1 && !l2 )    //两个都空，
            break;
        tail->next = malloc(sizeof(struct ListNode));
        tail = tail->next;
        tail->next = NULL;
    }
    if( carry > 0 )   //最高位有进位
    {
        tail->next = malloc(sizeof(struct ListNode));
        tail = tail->next;
        tail->val = carry;
        tail->next = NULL;
       
    }
    return head;
}


