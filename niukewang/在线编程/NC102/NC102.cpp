#include <queue>


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
     * @param o1 int整型
     * @param o2 int整型
     * @return int整型
     */
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        std::queue<std::pair<int,TreeNode*>> q;
        int indexfir = 0;
        int indexsec = 0;
        int res;

        q.push(std::make_pair(0, root));
        while (!q.empty()) {
            std::pair<int,TreeNode*> p = q.front();
            int index = p.first;
            TreeNode *node = p.second;

            q.pop();

            if(node->val == o1){
                indexfir = index;
            }else if(node->val == o2){
                indexsec = index;
            }

            if(indexfir && indexsec) break;

            if(node->left){
                q.push(std::make_pair(index * 2 + 1, node->left));
            }

            if(node->right){
                q.push(std::make_pair(index * 2 + 2, node->right));
            }
        }

        if(indexfir < indexsec){
            indexfir = (indexfir - 1)/2;
        }else{
            indexsec = (indexsec - 1)/2;
        }
        while (indexfir != indexsec) {
            if(indexfir < indexsec) indexsec = (indexsec - 1)/2;
            else indexfir = (indexfir - 1)/2;
        }

        while(!q.empty()) q.pop();

        q.push(std::make_pair(0, root));
        while(!q.empty()){
            std::pair<int, TreeNode*> p = q.front();
            int index = p.first;
            TreeNode *node = p.second;

            q.pop();

            if(index == indexfir){
                res = node->val;
                break;
            }

            if(node->left){
                q.push(std::make_pair(index * 2 + 1, node->left));
            }

            if(node->right){
                q.push(std::make_pair(index * 2 + 2, node->right));
            }
        }

        return res;
    }
};

int main(void){

    return 0;
}
