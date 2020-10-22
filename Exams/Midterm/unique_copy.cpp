template <classForwardIterator, classOutputIterator>OutputIterator unique_copy(ForwardIterator first, ForwardIterator last, OutputIterator result) {
	auto check = first;
	while (first != last) {
		++result;
		result = first;
		while (++check != last) {
			if (*first != *check)
				first = check;
		}
	}
	return result;
}

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

vector<int> findKMax(int arr[], size_t n, size_t k) {
	vector<int> better(n);
	for (int i = 0; i < n; i++) {
		better[i] = arr[i];
	}
	vector<int> final;
	make_heap(better.begin(), better.end());
	for (size_t j = 0; j < k; j++) {
		final.push_back(better.front());
		pop_heap(better.begin(), better.end());
	}
	return final;
}
