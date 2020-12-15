/* 
 * hungry_squirrel.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F19E2 Q25.
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

#include "hungry_squirrel.h"

using namespace std;

int helper(unordered_map<string, int>& memo, std::vector<std::vector<int>>& diag, int currRow, int currCol) {
	
	if (currCol == 0) return diag[currRow][currCol];
	
	int maxi = -1;
	if (currRow != 0) {
		string upDiag = to_string(currRow - 1) + "|" + to_string(currCol - 1);
		if (memo.find(upDiag) == memo.end()) {
			memo[upDiag] = helper(memo, diag, currRow - 1, currCol - 1);
		}
		maxi = max(maxi, memo[upDiag]);
	}
	else if (currRow != diag.size() - 1) {
		string downDiag = to_string(currRow + 1) + "|" + to_string(currCol - 1);
		if (memo.find(downDiag) == memo.end()) {
			memo[downDiag] = helper(memo, diag, currRow + 1, currCol - 1);
		}
		maxi = max(maxi, memo[downDiag]);
	}
	string back = to_string(currRow) + "|" + to_string(currCol - 1);
	if (memo.find(back) == memo.end()) {
		memo[back] = helper(memo, diag, currRow, currCol - 1);
	}
	return maxi = diag[currRow][currCol] + max(maxi, memo[back]);
}

int get_max_nuts(std::vector<std::vector<int>>& diag, int nrow, int ncol) {
	unordered_map<string, int> memo;
	int maxi = -1;
	for (int i = 1; i < nrow; ++i) {
		maxi = max(maxi, helper(memo, diag, nrow - i, ncol - 1));
	}
	return maxi;
}
