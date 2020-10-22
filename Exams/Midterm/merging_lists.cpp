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

Node* merge_lists(vector<Node*>& lists) {
	vector<int> solution;
	for (int i = 0; i < lists.size(); i++) {
		Node* curr = lists[i];
		while (curr) {
			solution.push_back(curr->val);
			curr = curr->next;
		}
	}
	sort(solution.begin(), solution.end());
	Node* sorted = new Node{ solution.at(0) };
	Node* jump = sorted;
	for (int i = 1; i < solution.size(); i++) {
		jump->next = new Node{ solution.at(i) };
		jump = jump->next;
	}
	return sorted;
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
}

/*Compile

g++ -Wall -Werror template.cpp -o test

*/