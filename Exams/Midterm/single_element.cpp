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

struct Node {
	int val;
	Node* next;
	Node() : val{ 0 }, next{ nullptr } {}
	Node(int x) : val{ x }, next{ nullptr } {}
	Node(int x, Node* next_in) : val{ x }, next{ next_in } {}
};

void node_print(Node* head) {
	Node* curr = head;
	while (curr != nullptr) {
		cout << curr->val << " -> ";
		curr = curr->next;
	}
	cout << "\n";
}

template <typename T>
void operator<<(ostream& os, const vector<T>& in) {
	for (auto i : in) {
		os << i << " ";
	}
	os << "\n";
}

int find_single_element(vector<int>& vec) {
	size_t left = 0;
	size_t right = vec.size() - 1;
	size_t mid = left + right / 2;
	while (mid != 0 && mid != (vec.size()-1)) {
		//If variable after middle is same must be in right side
		if (vec[mid] == vec[mid + 1]) {
			left = mid + 1;
			mid = left + right / 2;
		}
		else if (vec[mid] == vec[mid - 1]) {
			right = mid;
			mid = left + right / 2;
		}
		else
			return vec[mid];
		cout << mid << "\n";
	}
	return vec[mid];
}


int main() {
	//Nodes are in reverse order
	/*
	Node* one = new Node(370);
	Node* two = new Node(370, one);
	Node* three = new Node(281, two);
	Node* four = new Node(280, three);
	Node* five = new Node(280, four);
	node_print(five);
	*/
	vector<int> vec = { 0,0,1,1,2,2,3,3,4,4,5 };
	cout << find_single_element(vec);
}

/*Compile

g++ -Wall -Werror template.cpp -o test

*/