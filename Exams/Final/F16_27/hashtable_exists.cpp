/* 
 * hashtable_exists.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F16E2 Q27.
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

#include "hashtable_exists.h"

using namespace std;

bool exists(const HashTable &tbl, int val) {
	int M = (int)tbl.buckets.size();
	if (M == 0)
		return false;
	int compVal = val % M;
	int i = 1;
	while (tbl.status[compVal] != Status::Empty) {
		if (tbl.buckets[compVal] == val && tbl.status[compVal] == Status::Occupied)
			return true;
		else if (tbl.buckets[compVal] == val && tbl.status[compVal] == Status::Deleted)
			return false;
		compVal = ((compVal % M) + i * i) % M;
		++i;
	}
	return false;
}
