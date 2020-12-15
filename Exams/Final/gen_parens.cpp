/*
* zero_sum.cpp
* Univeristy of Michigan, Ann Arbor
* EECS 281 W19E2 Q25.
* SUBMIT ONLY THIS FILE TO GRADESCOPE.
*/

// Common #includes for convience.
// No need to use them. 
// Remove any of them if you want.
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

vector<string> helper(int n, unordered_map<int, vector<string>>& memo) {
	if (memo.find(n-1) == memo.end())
		memo[n - 1] = helper(n - 1, memo);
	vector<string> final;
	//Add () to front
	for (auto &i : memo[n - 1])
		final.push_back("()" + i);
	//Add () around n-1 
	for (auto &i : memo[n - 1])
		final.push_back("(" + i + ")");
	//Add () to back of n-1
	for (int i = 1; i < memo[n-1].size(); ++i) {
		final.push_back(memo[n - 1][i] + "()");
	}
	return final;
	
}

vector<string> generate_parentheses(int n) {
	unordered_map<int, vector<string>> memo;
	memo[0] = { "" };
	memo[1] = { "()" };
	return helper(n, memo);
}

int main() {
	vector<string> sam;
	sam = generate_parentheses(2);
	for (auto i : sam)
		cout << i << " ";
	cout << "\n";
	return 0;
}