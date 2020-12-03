/*
 * replace_words.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 7 Written.
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

#include "replace_words.h"

using namespace std;

vector<string> replace_words(const vector<string>& prefixes,
                             const vector<string>& sentence) {
    size_t largestPrefix = 0;
    unordered_map<string, int > map;
    map.reserve(prefixes.size());
    vector<string> final;
    final.reserve(sentence.size());

    for (auto i : prefixes) {
        if (i.size() > largestPrefix)
            largestPrefix = i.size();
        map[i] = 1;
    }

    bool pushed = false;

    for (auto i : sentence) {
        pushed = false;
        for (size_t j = 1; j <= largestPrefix && j <= i.size(); j++) {
            if (map[i.substr(0, j)]) {
                final.push_back(i.substr(0, j));
                pushed = true;
                break;
            }
        }
        if (!pushed)
            final.push_back(i);
    }

  return final;
}
/*
int main() {
    vector<string> prefixes{ "cat", "bat", "rat" };
    vector<string> sentence{ "the", "cattle", "was", "rattled", "by", "the", "battery" };
    vector<string> out = replace_words(prefixes, sentence);
    for (auto i : out) {
        cout << i << " ";
    }
    cout << "\n";
}
*/