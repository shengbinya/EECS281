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

using namespace std;

int sum_remnant_values(const std::vector<int>& seq, int k) {
	deque<int> consecutive;
	vector<int> final;
	int curr_consecutive = 0;
	for (int i = 0; i < seq.size()-1; i++) {
		consecutive.push_front(seq[i]);
		if (seq[i + 1] == seq[i]) {
			curr_consecutive++;
		}
		else if (curr_consecutive >= k) {
			for (int comp = seq[i]; consecutive.front() == comp; curr_consecutive = 0) {
					consecutive.pop_front();
			}
		}
		else {
			for (; curr_consecutive < consecutive.size() && consecutive[curr_consecutive] == seq[i]; curr_consecutive++) {
				if (curr_consecutive > k) {
					curr_consecutive = -1;
					break;
				}
				if (curr_consecutive == -1) {
					for (int comp = seq[i]; consecutive.front() == comp; curr_consecutive = 0) {
						consecutive.pop_front();
					}
				}
					
			}
		}	
	}
	int num = 0;
	while (!consecutive.empty()) {
		num += consecutive.front();
		consecutive.pop_front();
	}
	return num;
}


template <class ForwardIterator1, class ForwardIterator2, class Predicate>
bool sequence_contains(ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	Predicate pred) {
	while (first1 != last1 && first2 != last2) {
		if (pred(*first1, *first2)) {
			first1++;
		}
		else if (pred(*first2, first1*)) {
			return false;
		}
		else {
			first1++;
			first2++;
		}
	}
	return first1 == last1 ? true : false;
}