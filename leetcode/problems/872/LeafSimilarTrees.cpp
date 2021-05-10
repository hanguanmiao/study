#include <queue>
#include <vector>
#include <iostream>

 // Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        std::vector<int> vals1;
        getValOfleaves(root1, vals1);
        std::vector<int> vals2;
        getValOfleaves(root2, vals2);
        return (vals1 == vals2);
    }

private:
    void getValOfleaves(TreeNode *node, std::vector<int> &vals){
        bool isleaf = true;
        if(node->left){
            isleaf = false;
            getValOfleaves(node->left, vals);
        }
        if(node->right){
            isleaf = false;
            getValOfleaves(node->right, vals);
        }
        if(isleaf){
            vals.push_back(node->val);
        }
    }
};


int main(void){
    Solution s;
    TreeNode node1(7), node2(4);
    TreeNode node3(6), node4(2, &node1, &node2);
    TreeNode node5(5, &node3, &node4);
    TreeNode node6(9), node7(8);
    TreeNode node8(1, &node6, &node7);
    TreeNode root1(3, &node5, &node8);

    TreeNode node9(9), node10(8);
    TreeNode node11(4), node12(2, &node9, &node10);
    TreeNode node13(1, &node11, &node12);
    TreeNode node14(6), node15(7);
    TreeNode node16(5, &node14, &node15);
    TreeNode root2(3, &node16, &node13);

    std::cout << s.leafSimilar(&root1, &root2) << std::endl;

    return 0;
}
