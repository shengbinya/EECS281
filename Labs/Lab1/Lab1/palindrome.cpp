/* 
 * palindrome.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 1 Written.
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

#include "palindrome.h"

using namespace std;

bool isPalindrome(Node* start, Node* end) {
	
	while (start != end && start != end->prev) {
		if (start->value != end->value)
			return false;
		start = start->next;
		end = end->prev;
	}
	
	return true;
}
