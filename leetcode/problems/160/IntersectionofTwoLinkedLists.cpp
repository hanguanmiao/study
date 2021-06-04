#include <unordered_set>

using namespace std;

//  Definition for singly-linked list.
struct ListNode {

    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(nullptr == headA || nullptr == headB) return nullptr;

        unordered_set<ListNode*> unset;
        ListNode *node = headA;
        while (node) {
            unset.insert(node);
            node = node->next;
        }
        node = headB;
        while (node) {
            if(unset.count(node)) return node;
            node = node->next;
        }
        return nullptr;
    }
};
