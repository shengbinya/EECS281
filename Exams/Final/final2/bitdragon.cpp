/*
 * bitdragon.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F20E2 Q26.
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

#include "bitdragon.h"

using namespace std;

int hire_heroes(const vector<int> &experience, const vector<vector<int>> &partners, int k) {
  //create a vector that contains the number of people that are working in a group and the experience of that group
  //iterate over vector to find most experienced group < k
  //Add heroes to queue and add them to unordered_set once they've been discovered
	vector<pair<int, int>> partyInfo;
	unordered_set<int> inParty;
	for (int i = 0, partyNum = 0; i < (int)partners.size(); ++i) {
		//If not already in a party
		if (inParty.find(i) == inParty.end()) {
			deque<pair<int, int>> find_members;
			find_members.push_back({ partyNum, i });
			partyInfo.push_back({ 0,0 });
			partyNum++;
			while (!find_members.empty()) {
				//Add all party members to queue
				for (auto &j : partners[find_members.front().second]) {
					find_members.push_back({ find_members.front().first, j });
				}
				inParty.insert(find_members.front().second);
				partyInfo[find_members.front().first].first++;
				partyInfo[find_members.front().first].second += experience[find_members.front().second];
				find_members.pop_front();
			}

		}
		
	}
	int bestExperience = 0;
	for (auto i : partyInfo) {
		if (i.first < k && i.second > bestExperience)
			bestExperience = i.second;
	}

  return bestExperience;
}
