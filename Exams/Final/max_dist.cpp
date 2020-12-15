//Problem 122 Solution
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

int max_repeated_distance(const vector<int>& vec) {
	unordered_map<size_t, int> map;
	int max_distance = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (map.find(vec[i]) == map.end()) {
			map[vec[i]] = i;
		}
		else{
			if (i - map[vec[i]] > max_distance)
				max_distance = i - map[vec[i]];
		}
	}
	return max_distance;
}

int main() {
	vector<int> vec = { 1, 2, 3, 2, 2, 1, 3, 3, 2 };
	cout << max_repeated_distance(vec) << endl;
}