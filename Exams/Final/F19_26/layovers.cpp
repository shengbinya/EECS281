/* 
 * layovers.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F19E2 Q26.
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

#include "layovers.h"

using namespace std;

int helper(unordered_map<string, vector<string>>& memo, string origin, string dest) {
	if (origin == dest)
		return 0;

	int mini = numeric_limits<int>::infinity(); 
	for (auto& i : memo[dest]) {
		int comp = 1 + helper(memo, origin, i);
		mini = min(mini, comp);
	}
	return mini;
}

int fewest_layovers(vector<vector<string>>& flights, string origin, string dest) {
	unordered_map<string, vector<string>> memo;
	for (auto& i : flights) {
		if (memo.find(i[1]) == memo.end())
			memo[i[1]] = vector<string>(1,i[0]);
		else
			memo[i[1]].push_back(i[0]);
	}
	int out = helper(memo, origin, dest);
	cout << out << "\n";
	if (out == numeric_limits<int>::infinity())
		return -1;
	return out;
}

