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

struct Interval {
	int start;
	int end;
};

struct comp {
	bool operator()(Interval const& l, Interval const& r) {
		return l.start < r.start;
	}
};
vector<Interval> merge_intervals(vector<Interval>& vec) {
	sort(vec.begin(), vec.end(), [](Interval a, Interval b) {return a.start < b.start; });
	vector<Interval> solution;
	Interval curr{ vec.at(0).start, vec.at(0).end };

	for (size_t i = 1; i < vec.size(); ++i) {
		if (curr.end >= vec.at(i).start)
			curr.end = vec.at(i).end;
		else {
			solution.push_back(curr);
			curr.start = vec.at(i).start;
			curr.end = vec.at(i).end;
		}
	}
	return solution;
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
	Interval one{ 1,3 };
	Interval two{ 2,6 };
	Interval three{ 8,10 };
	Interval four{ 15,18 };
	
	
	vector<Interval> 
}

/*Compile

g++ -Wall -Werror template.cpp -o test

*/