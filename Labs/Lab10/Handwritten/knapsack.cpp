/* 
 * knapsack.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 10 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
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

#include "knapsack.h"

using namespace std;

int knapsack(int C, const vector<int>& value, const vector<int>& weight) {
	size_t itemNum = value.size();
	vector<vector<int>> memo(itemNum + 1, vector<int>(C + 1, 0));

	for (size_t currItem = 0; currItem < itemNum; ++currItem) {
		for (size_t currCap = 0; currCap < C + 1; ++currCap) {
			//If we can fit into knapsack
			if (weight[currItem] <= currCap) {
				memo[currItem + 1][currCap] = max(memo[currItem][currCap], memo[currItem][currCap - weight[currItem]] + value[currItem]);
			}
			//Copy the optimized value from above
			else
				memo[currItem + 1][currCap] = memo[currItem][currCap];
		}
	}

	return memo[itemNum][C];
}

