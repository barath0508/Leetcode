/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
 * };
 */

class Solution {
public:
    // 1) Inorder traversal to collect sorted values
    void inorder(TreeNode* root, vector<int> &vals) {
        if (!root) return;
        inorder(root->left, vals);
        vals.push_back(root->val);
        inorder(root->right, vals);
    }

    // 2) Build balanced BST from sorted values
    TreeNode* buildBalanced(const vector<int> &vals, int l, int r) {
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;          // middle element
        TreeNode* root = new TreeNode(vals[mid]);
        root->left  = buildBalanced(vals, l, mid - 1);
        root->right = buildBalanced(vals, mid + 1, r);
        return root;
    }

    TreeNode* balanceBST(TreeNode* root) {
        vector<int> vals;
        inorder(root, vals);                // step 1
        return buildBalanced(vals, 0, (int)vals.size() - 1);  // step 2
    }
};
