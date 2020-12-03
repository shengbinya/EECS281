struct BinaryTreeNode {
  BinaryTreeNode* left;
  BinaryTreeNode* right;
  int value;
  BinaryTreeNode(int n) : left{nullptr}, right{nullptr}, value{n} {}
};

int diameter(const BinaryTreeNode* tree);
