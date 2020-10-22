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

vector<int> prev_greatest_element(vector<int>& vec) {
	vector<int> solution(0, vec.size());
	int prevGreatest = -1;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (i != vec.size()-1 && vec[i] > vec[i + 1]) {
			solution.push_back(prevGreatest);
			prevGreatest = vec[i];
		}
		else
			solution.push_back(prevGreatest);
	}
	return solution;
}

template <typename T>
void operator<<(ostream& os, const vector<T> & in) {
	for (auto i : in) {
		os << i << " ";
	}
	os << "\n";
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

	vector<int> example = { 11, 16, 15, 13 };
	cout << prev_greatest_element(example);
}

/*Compile

g++ -Wall -Werror previous_greater.cpp -o test

*/