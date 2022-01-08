


  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *headLess = nullptr,
                *tailLess = nullptr,
                *headGreat = nullptr,
                *tailGreat = nullptr;

        while(head){
            if(head->val < x){
                if(headLess){
                    tailLess->next = head;
                    tailLess = head;
                }else{
                    headLess = tailLess = head;
                }
                head = head->next;
                tailLess->next = nullptr;
            }else {
                if(headGreat){
                    tailGreat->next = head;
                    tailGreat = head;
                }else{
                    headGreat = tailGreat = head;
                }
                head = head->next;
                tailGreat->next = nullptr;
            }
        }

        if(tailLess){
            tailLess->next = headGreat;
        }else{
            headLess = headGreat;
        }

        return headLess;
    }
};

  class Solution {
  public:
      ListNode* partition(ListNode* head, int x) {
          ListNode* small = new ListNode(0);
          ListNode* smallHead = small;
          ListNode* large = new ListNode(0);
          ListNode* largeHead = large;
          while (head != nullptr) {
              if (head->val < x) {
                  small->next = head;
                  small = small->next;
              } else {
                  large->next = head;
                  large = large->next;
              }
              head = head->next;
          }
          large->next = nullptr;
          small->next = largeHead->next;
          return smallHead->next;
      }
  };


void test(void);
void test1(void);

int main(void){
    test();
    return 0;
}


void test(void){
    test1();

}
void test1(void){
    ListNode *head;
    ListNode node1(1);
    ListNode node2(4);
    ListNode node3(3);
    ListNode node4(2);
    ListNode node5(5);
    ListNode node6(2);
    ListNode *res;
    Solution s;

    node5.next = &node6;
    node4.next = &node5;
    node3.next = &node4;
    node2.next = &node3;
    node1.next = &node2;
    head = &node1;

    res = s.partition(head, 3);
}
