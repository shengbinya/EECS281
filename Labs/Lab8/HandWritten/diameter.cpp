#include "diameter.h"

int helper(const BinaryTreeNode* tree, int& largest) {
	if (!tree)
		return 0;
	int l = helper(tree->left, largest);
	int r = helper(tree->right, largest);
	if (r + l > largest)
		largest = l + r;
	return l < r ? r + 1 : l + 1;
}

int diameter(const BinaryTreeNode* tree) {
	int largest = 0;
	helper(tree, largest);
	return largest;
}

