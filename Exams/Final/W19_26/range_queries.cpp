/*
 * range_queries.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 W19E2 Q26.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them.
// Remove any of them if you want.
#include "range_queries.h"

#include <math.h>

#include <algorithm>
#include <cassert>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

void range_queries(const std::vector<unsigned int>& data,
                   const std::vector<Query>& queries) {
    unordered_map<unsigned int, vector<int>> memo;
    for (auto i : data) {
        if (memo.find(i) == memo.end()) {
            memo[i] = vector<int>(data.size(), -1);
        }
    }
    for (auto i : data) {
        if (memo[i][0] == -1) {
            data[0] == i ? memo[i][0] = 1 : memo[i][0] = 0;
            for (size_t j = 1; j < data.size(); ++j) {
                memo[i][j] = (i == data[j]) ? 1 + memo[i][j - 1] : memo[i][j - 1];
            }
        }
    }
    for (auto &i : queries) {
        if (memo.find(i.id) != memo.end() && i.start != 0)
            cout << memo[i.id][i.end] - memo[i.id][i.start-1] << " ";
        else if (memo.find(i.id) != memo.end()) 
            cout << memo[i.id][i.end] << " ";
        else
            cout << 0 << " ";
    }
    cout << "\n";
}
/*
int main() {
    vector<unsigned int> data = { 5,4,3,5,3,3,2,1,3 };
    vector<Query> query = { {4,7,8}, {3,0,3}, {3,0,8}, {7,0,8}, {5,0,4} };
    range_queries(data, query);
}
*/
