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

int main() {
	//Nodes are in reverse order
	
	Node* one = new Node(370);
	Node* two = new Node(370, one);
	Node* three = new Node(281, two);
	Node* four = new Node(280, three);
	Node* five = new Node(280, four);
	Node* check = new Node(280);
	node_print(five);

}

/*Compile 

g++ -Wall -Werror template.cpp -o test

*/