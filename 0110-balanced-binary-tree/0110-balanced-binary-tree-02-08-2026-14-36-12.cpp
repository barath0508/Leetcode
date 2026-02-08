// LeetCode definition:
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right)
//         : val(x), left(left), right(right) {}
// };

class Solution {
public:
    // returns height if subtree is balanced, otherwise -1
    int checkHeight(TreeNode* node) {
        if (!node) return 0;                 // empty subtree has height 0

        int leftH = checkHeight(node->left); // height of left subtree
        if (leftH == -1) return -1;          // left subtree already unbalanced

        int rightH = checkHeight(node->right); // height of right subtree
        if (rightH == -1) return -1;           // right subtree already unbalanced

        if (abs(leftH - rightH) > 1)          // current node violates balance
            return -1;

        return 1 + max(leftH, rightH);        // height of current subtree
    }

    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }
};
