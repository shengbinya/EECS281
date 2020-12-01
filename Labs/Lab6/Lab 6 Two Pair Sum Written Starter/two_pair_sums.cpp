/* 
 * two_pair_sums.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 6 Written.
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

#include "two_pair_sums.h"

using namespace std;

void two_pair_sums(const vector<int>& nums, ostream& os) {
	if (nums.empty()) return;
	map<pair<int, int>, int> valMap;
	for (auto i = nums.begin(); i+1 != nums.end(); ++i) {
		for (auto j = i+1; j != nums.end(); ++j) {
			valMap[pair<int, int>(*i, *j)] = *i+*j;
		}
	}
	for (auto i = valMap.begin(); i != valMap.end(); ++i) {
		for (auto j = i; j != valMap.end();) {
			++j;
			if (i->second == j->second) {
				if (i->first != j->first) {
					os << "(" << i->first.first << "," << i->first.second << ") and ("
						<< j->first.first << "," << j->first.second << ")\n";
				}
			}
		}
	}

}

/*
int main() {
	vector<int> nums = { 3,4,7,1,2,8 };
	two_pair_sums(nums, cout);
}
*/

