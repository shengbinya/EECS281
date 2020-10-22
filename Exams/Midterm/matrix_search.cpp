#include <vector>
using namespace std;

int find_rotated_minimum(vector<int>& vec) {
	int left = 0;
	int right = vec.size() - 1;
	int mid = left + right / 2;

	while (mid != left && mid != right) {
		(vec[mid] < vec.at(0)) ? right = mid : left = mid;
		mid = (right + left) / 2;
	}

	return vec[left] > vec[left + 1] ? vec[left] : vec[left + 1];
}