// Project Identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768
// Partner Brendan Nell bnelll@umich.edu
// Matt Martin mgmii@umich.edu

#include <iostream>
#include <iterator>
#include <deque>
#include <string>

using namespace std;
//(), [] and {}.

int main() {
	std::istream_iterator<char> eos;              
	std::istream_iterator<char> iit(std::cin);

	deque<char> input;
	

	while (iit != eos) {
		if(*iit == '(' || *iit == '[' || *iit == '{') {
			input.push_front(*iit);
		}
		else if (*iit == ')') {
			if (input.size() != 0 && input.at(0) == '(')
				input.pop_front();
			else {
				cout << "Not balanced\n";
				return 0;
			}
		}
		else if (*iit == '}') {
			if (input.size() != 0 &&  input.at(0) == '{')
				input.pop_front();
			else {
				cout << "Not balanced\n";
				return 0;
			}
		}
		else if (*iit == ']') {
			if (input.size() != 0 && input.at(0) == '[')
				input.pop_front();
			else {
				cout << "Not balanced\n";
				return 0;
			}
		}
		++iit;
	}
	if (input.size() == 0)
		cout << "Balanced\n";
	else
		cout << "Not balanced\n";
	return 0;
}