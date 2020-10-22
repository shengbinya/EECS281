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


Node* reverse_list(Node* list) {
	Node* curr = list;
	Node* prev = curr;
	Node* next = curr->next;
	
	curr->next = nullptr;
	curr = next;

	while (curr->next) {
		next = curr->next;
		curr->next = prev;
		curr = next;
	}
	curr->next = prev;
	return curr;
}

Node* add_lists(Node* list1, Node* list2) {
	list1 = reverse_list(list1);
	list2 = reverse_list(list2);
	
	Node* it1 = list1;
	Node* it2 = list2;
	int remainder;
	Node* begin = new Node{};
	Node* curr = begin;
	
	while (it1 || it2) {
		if (it1 && it2) {
			curr->val = (curr->val + it1->val + it2->val) % 10;
			Node* next = new Node{ (curr->val + it1->val + it2->val) / 10, nullptr };
			curr->next = next;
			curr = curr->next;
			it1 = it1->next;
			it2 = it2->next;
		}
		if(it1){
			curr->val = (curr->val + it1->val) % 10;
			Node* next = new Node{ (curr->val + it1->val) / 10, nullptr };
			curr->next = next;
			curr = curr->next;
			it1 = it1->next;
		}
		else {
			curr->val = (curr->val + it2->val) % 10;
			Node* next = new Node{ (curr->val + it2->val) / 10, nullptr };
			curr->next = next;
			curr = curr->next;
			it2 = it2->next;
		}
		
	}

	return reverse_list(begin);
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