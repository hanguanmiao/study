#include <stack>



//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


//class Solution {
//public:
//    int rangeSumBST(TreeNode* root, int low, int high) {
//        std::stack<TreeNode *> stk;
//        int sum = 0;

//        stk.push(root);
//        while(!stk.empty()){
//            TreeNode *node = stk.top();
//            int val = node->val;

//            stk.pop();
//            if(low <= val && val <= high) sum += val;
//            if(low < val && node->left) stk.push(node->left);
//            if(val < high && node->right) stk.push(node->right);
//        }

//        return sum;
//    }
//};

class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        std::stack<TreeNode *> stk;
        int sum = 0;

        stk.push(root);
        while(!stk.empty()){
            TreeNode *node = stk.top();
            int val = node->val;

            stk.pop();

            if(val < low){
                if(node->right) stk.push(node->right);
            }else if (val == low) {
                sum += val;
                if(low != high && node->right) stk.push(node->right);
            }else if(low < val && val < high){
                sum += val;
                if(node->right) stk.push(node->right);
                if(node->left) stk.push(node->left);
            }else if(val == high){
                sum += val;
                if(node->left) stk.push(node->left);
            }else{
                if(node->left) stk.push(node->left);
            }
        }

        return sum;
    }
};

#include <vector>
int main(void){

    return 0;
}
