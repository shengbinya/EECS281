/*
 * anagram.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 3 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them.
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
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

#include "anagram.h"

using namespace std;

bool isAnagram(const string &s1, const string &s2) {
  
	map<char, int> table = {
		{'a', 2},
		{'b', 3},
		{'c', 5},
		{'d', 7},
		{'e', 11},
		{'f', 13},
		{'g', 17},
		{'h', 19},
		{'i', 23},
		{'j', 29},
		{'k', 31},
		{'l', 37},
		{'m', 37},
		{'n', 41},
		{'o', 43},
		{'p', 53},
		{'q', 59},
		{'r', 61},
		{'s', 67},
		{'t', 71},
		{'u', 73},
		{'v', 79},
		{'w', 83},
		{'x', 89},
		{'y', 97},
		{'z', 101},
		{' ', 1}
	};

	size_t size1 = 1;
	size_t size2 = 1;

	for (size_t i = 0; i < s1.size(); i++){
		size1 *= table[s1[i]];	
	}
	for (size_t i = 0; i < s2.size(); i++) {
		size2 *= table[s2[i]];
	}
	if (size1 == size2)
		return true;
	return false;
}
