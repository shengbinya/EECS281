#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int helper(unordered_map<string, int> &memo, int M, int N, int X) {
	if (N == 0)
		return 0;
	int sum = 0;
	for (int i = M; i >= 1; --i) {
		if (memo.find(to_string(X - i) + "|" + to_string(N - 1)) == memo.end())
			memo[to_string(X - i) + "|" + to_string(N - 1)] = helper(memo, M, N - 1, X - i);
		sum += memo[to_string(X - i) + "|" + to_string(N - 1)];
	}
	return sum;
}

int find_ways(int M, int N, int X) {
	unordered_map<string, int> memo;
	for (int i = 1; i <= M; ++i) {
		memo[to_string(i) + "|1"] = 1;
	}
	return helper(memo, M, N, X);
}

int find_ways2(int M, int N, int X) {
	vector<vector<int>> memo(N + 1, vector<int>(X + 1));
	for (int j = 1; j <= M && j <= X; ++j) {
		memo[1][j] = 1;
	}
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j <= X; ++j) {
			for (int k = 1; k <= M && k < j; ++k) {
				memo[i][j] += memo[i - 1][j - k];
			}
		}
	}
	return memo[N][X];
}

int main() {
	cout << find_ways(6, 5, 12) << "\n";
	cout << find_ways2(6, 5, 12) << "\n";
}