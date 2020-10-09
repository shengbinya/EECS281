/* 
 * sort012.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 5 Written.
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

#include "sort012.h"

using namespace std;

void sort012(vector<int>& nums) {

	int index0 = 0;
	int index2 = nums.size()-1;
	
	for (auto i : nums) {
		cerr << i << ",";
	}
	cerr << "\n";
	

	for (int i = 0; i < nums.size(); i++) {
		if (i == 7) {
			int j = 0;
			j += j;
		}
		
		if (nums[i] == 0) {
			swap(nums[index0], nums[i]);
			++index0;
			if (nums[i] == 2 || nums[i] == 0) {
				while (nums[i] != 1 && i >= index0 && i <= index2) {

					if (nums[i] == 0) {
						swap(nums[index0], nums[i]);
						++index0;
					}
					else if (nums[i] == 2) {
						swap(nums[index2], nums[i]);
						--index2;
					}
			}
			

			}
			
		}
		else if (nums[i] == 2) {
			swap(nums[index2], nums[i]);
			--index2;
			if(nums[i] == 0 || nums[i] == 2)
			{
				while (nums[i] != 1 && i >= index0 && i <= index2) {

					if (nums[i] == 0) {
						swap(nums[index0], nums[i]);
						++index0;
					}
					else if (nums[i] == 2) {
						swap(nums[index2], nums[i]);
						--index2;
					}
			}
			

			}
		}
		if (i >= index2 || i == nums.size() - 1) {
			break;
		}
		
		for (auto i : nums) {
			cerr << i << ",";
		}
		cerr << "\n";
		
	}
	
}


int main() {
	vector<int> nums = { 0,1,2,0,1,2,0,1,2,0,1,2 };
	sort012(nums);
	for (auto i : nums) {
		cout << i << ",";
	}
	cout << "\n";
}



