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

// A iterative binary search function. It returns 
// location of x in given array arr[l..r] if present, 
// otherwise -1 
int binarySearch(vector<int> vec,  int x) {
    int l = 0, r = vec.size();
    while (l <= r) {
        int m = (l + r) / 2;

        // Check if x is present at mid 
        if (vec[m] == x)
            return m;

        // If x greater, ignore left half 
        if (vec[m] < x)
            l = m + 1;

        // If x is smaller, ignore right half 
        else
            r = m - 1;
    }

    // if we reach here, then element was 
    // not present 
    return -1;
}

// Concise
int binarySearch(vector<int> vec, int x) {
    int l = 0, r = vec.size() - 1;
    while (l < r) {
        int m = (l + r) / 2;

        // If x greater, ignore left half 
        if (vec[m] < x)
            l = m + 1;

        // If x is smaller, ignore right half 
        else
            r = m;
    }
    //We assume that the value has to be in the search vector 
    return l;
}

vector<int> find_closest_elements(vector<int>& vec, int k, int target) {
    int l = 0, r = vec.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        // If x greater, ignore left half 
        if (vec[m + k / 2] < target)
            l = m + 1;
        // If x is smaller, ignore right half 
        else if (vec[m - k / 2] > target)
            r = m - 1;
        else
            l = m - k / 2;
    }
    while (vec[l] != target) {
        l++;
    }
    vector<int> end(k);
    for (int i = l - k / 2; i < l - k / 2 + k; l++) {
        end[i] = vec[i];
    }
    return end;
}


template <class ForwardIterator1, class ForwardIterator2, class OutputIterator, class Compare>
OutputIterator set_difference(ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2,
    OutputIterator result, Compare comp) {
    while (first1 != last1) {
        if (comp(first1, first2)) {
            *result = *first1;
            first1++;
        }
        else if (comp(first1, first2)) {
            first2++;
        }
        else {
            first1++;
            first2++;
        }
    }
    return result;
}

template <class ForwardIterator, class Compare>
pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator first,
    ForwardIterator last, Compare comp) {
    auto smallest = first, largest = last;
    while (first != last) {
        if (comp(*first, *smallest)) {
            smallest = first;
        }
        else if (*largest, *first) {
            largest = first;
        }
        else
            largest = first;
        first++;
    }
    return pair<ForwardIterator, ForwardIterator> {smallest, largest};
}

struct Node {
    int val;
    Node* left;
    Node* right;
};


void copy(vector<int>& in, vector<Node *> ptrs, Node* ptr) {
    if (!ptr)
        return;
    in.push_back(ptr->val);
    ptrs.push_back(ptr);
    copy(in, ptrs, ptr->left);
    copy(in, ptrs, ptr->right);
}

void linearize(Node* binary_heap) {
    vector<int> vals;
    vector<Node*> ptrs;
    copy(vals, ptrs, binary_heap->right);
    copy(vals, ptrs, binary_heap->left);
    binary_heap->left = ptrs[0];
    binary_heap->right = nullptr;
    vals.push_back(binary_heap->val);
    for (int i = 0; i < vals.size(); i++) {
        ptrs[i]->left = ptrs[i+1];
        ptrs[i]->right = nullptr;
    }
    make_heap(vals.begin(), vals.end());
    for (int i = 1; i < ptrs.size(); i++) {
        ptrs[i-1]->val = vals[i];
    }
}
