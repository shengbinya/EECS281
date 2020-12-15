//Problem 121 Solution
#include <vector>
#include <iostream>

using namespace std;

int min_helper(int h, vector<int> &calculated) {
	if (h <= 0)
		return 0;
	if (calculated[h] == 0) {
		calculated[h] = 1 + min_helper(h - 1, calculated) + min_helper(h - 2, calculated);
	}
	return calculated[h];
}

int min_nodes_in_AVL(int h) {
	vector<int> calculated(h + 1);
	return min_helper(h, calculated);
}

int main() {
	cout << min_nodes_in_AVL(5) << endl;
}