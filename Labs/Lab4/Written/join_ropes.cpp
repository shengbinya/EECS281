/* 
 * join_ropes.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 4 Written.
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

#include "join_ropes.h"

using namespace std;

int join_ropes(const vector<int>& rope_lengths) {
	vector<int> final = rope_lengths;
	vector<int> sums;
	int total = 0;
	while (final.size() > 1) {
		std::sort(final.begin(), final.end());
		
		sums.push_back(final.at(0) + final.at(1));
		
		final.erase(final.begin(),final.begin()+2);
		final.push_back(sums.at(sums.size() - 1));

	}
	for (auto i : sums) {
		total += i;
	}
	return total;
}
