#include <queue>

using namespace std;

  struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
  };


class Solution {
public:
    /**
     *
     * @param root TreeNode类
     * @return int整型vector<vector<>>
     */
    vector<vector<int> > levelOrder(TreeNode* root) {
        vector<vector<int>> res;

        if(!root) return res;
        else q.push(root);

        while (!q.empty()) {
            size_t size = q.size();
            vector<int> vs;
            for(size_t i=0; i<size; ++i){
                TreeNode *node = q.front();

                q.pop();

                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
                vs.push_back(node->val);
            }
            res.push_back(std::move(vs));
        }

        return res;
    }

private:
    queue<TreeNode*> q;
};

int main(void){


    return 0;
}
