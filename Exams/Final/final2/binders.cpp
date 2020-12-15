/*
 * binders.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F20E2 Q25.
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "binders.h"

using namespace std;

int min_combine_cost(const vector<vector<int>> &binders) {

	for (int i = 0; i < (int)binders.size(); ++i) {
		vector<vector<vector<int>, pair<int, int>, int>>> memo;
		memo.reserve(binders.size() * binders.size());
		for (int j = 0; j < (int)binders.size(); ++j) {
			for (int k = j + 1; k < (int)binders.size(); ++k) {
				vector<int> comb;
				memo.push_back(rand, { {j, k} , combine(memo[j], memo[k], rand) });
			}
		}
		pair<int, int> smallestCombine;
		int max = numeric_limits<int>::infinity();
		for (auto& i : memo) {
			if (i.second < max) {
				max = i.second;
				smallestCombine = i.first;
			}
		}
	}
	return 0;
}



//Create memo hash table for easy lookup of cost of all combined
/*
unordered_map<string, pair<int, vector<int>>> memo;
for (int i = 0; i < (int)binders.size(); ++i) {
	for (int j = i + 1; j < (int)binders.size(); ++j) {
		vector<int> out;
		int val = combine(binders[j], binders[i], out);
		memo[to_string(i) + "|" + to_string(j)] = pair<int, vector<int>>{ val, out };
	}
}
*/