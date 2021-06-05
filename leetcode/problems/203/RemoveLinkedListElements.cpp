
using namespace std;



  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode prehead(0, head);
        ListNode *pre = &prehead, *cur = head;
        while (cur) {
            if(cur->val == val){
                pre->next = cur->next;
                cur = cur->next;
            }else {
                pre = cur;
                cur = cur->next;
            }
        }
        return prehead.next;
    }
};
int main(void){

}
