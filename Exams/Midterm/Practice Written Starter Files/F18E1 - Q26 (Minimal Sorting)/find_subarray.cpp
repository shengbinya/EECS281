/*
 * find_subarray.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F18E1 Q26.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

 // Common #includes for convience.
 // No need to use them. 
 // Remove any of them if you want.

#include <algorithm>
#include <cassert>
#include <climits>
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

#include "find_subarray.h"

using namespace std;

void find_subarray(const std::vector<int>& v) {
	int firstNegDiffSum = 0, firstNegIndx = -1, lastNegDiffSum = 0, lastNegDiffIndx = -1, currSum = 0;
	for (int i = 0; i < v.size()-1; i++) {
		if (firstNegIndx == -1) //Sum til first drop
			firstNegDiffSum += v[i + 1] - v[i];
		if (0 > (v[i + 1] - v[i]))//Find last drop
			lastNegDiffIndx = i;
		if (0 > (v[i + 1] - v[i]) && firstNegIndx == -1) //Find the first drop
			firstNegIndx = i;
  }
	for (int i = 0; i < v.size() - 1; i++) {
		currSum += v[i + 1] - v[i]; //Cout index once first neg diff sum exceeded
		if (currSum > firstNegDiffSum && i <= firstNegIndx) {
			cout << "Sort from index " << i+1 << " to index ";
			currSum = 0;}
		if (i > lastNegDiffIndx && currSum > 0) {
			if (firstNegDiffSum < 0)
				cout << "Sort from index " << 0 << " to index ";
			cout << i << "\n";
			return;}
	}
	cout << v.size()-1 << "\n";
}


int main() {
	vector<int> fish{12, 1,0,3,-40 };
	find_subarray(fish);
}


