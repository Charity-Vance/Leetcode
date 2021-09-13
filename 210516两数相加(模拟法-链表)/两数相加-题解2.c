/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
      struct ListNode * l3 = (struct ListNode *)malloc(sizeof(struct ListNode));
       struct ListNode * head=l3,*p;
      int result=0,flag=0;
      while(l1!=NULL||l2!=NULL){
          if(l1!=NULL){
              result+=l1->val;
              l1=l1->next;
          }
          if(l2!=NULL){
              result+=l2->val;
              l2=l2->next;
          }
          result+=flag;
          flag=0;
          flag=result/10;
          
           l3->val=result%10;
           
            
                l3->next=(struct ListNode *)malloc(sizeof(struct ListNode));
                p=l3;
            l3=l3->next;
            
             result=0;
      }
           if(flag!=0){
               l3->val=flag;
               l3->next=NULL;
               return head;
           }
            p->next=NULL;
        
        return head;
        
}
