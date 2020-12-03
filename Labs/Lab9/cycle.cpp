/* 
 * cycle.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 9 Written.
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

#include "cycle.h"

using namespace std;

bool is_graph_cyclic(const vector<vector<int>> &adj_list) {
	/*vector<pair<int, int>> unionFind;
	unionFind.reserve(adj_list.size());
	for (size_t i = 0; i < adj_list.size(); ++i) {
		unionFind.push_back(pair<int,int>{ i,i });
	}

	for (size_t i = 0; i < adj_list.size(); ++i) {
		// Find the real root of the value at beginning of list
		int val = unionFind[i].second;
		while (unionFind[val].second != val) {
			val = unionFind[val].second;
		}
		for (size_t j = 0; j < adj_list[i].size(); ++j) {
			//Find real root of right node
			int valR = unionFind[adj_list[i][j]].second;
			while (unionFind[valR].second != valR) {
				valR = unionFind[valR].second;
			}
			
			//Check if the real root of right node is same as real root of left node
			if (val == valR && (i- adj_list[i][j]) != 1)
				return true;
			else if((i - adj_list[i][j]) != 1)// make the connection
				unionFind[adj_list[i][j]].second = i;
		}
	}
	return false;
	*/
	if (adj_list.size() == 0 || adj_list.size() == 1)
		return false;
	int totalEdges = 0;
	for (auto k : adj_list) {
		totalEdges += k.size();
	}
	totalEdges -= adj_list.size();
	if (adj_list.size() > totalEdges)
		return false;
	else
		return true;
}
/*
int main() {
	vector<vector<int>> main;
	main.push_back(vector<int>{1});
	main.push_back(vector<int>{0,2,4});
	main.push_back(vector<int>{1,3,4});
	main.push_back(vector<int>{2});
	main.push_back(vector<int>{1,2});
	cout << is_graph_cyclic(main) << "\n";
}
*/



