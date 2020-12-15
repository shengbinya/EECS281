#include <vector>
#include <iostream>
#include <limits>

using namespace std;

//Given in problem
vector<string> single_turn_seqs(string& orig_seq) {
	vector<string> result;
	for (int i = 0; i < 4; ++i) {
		string temp = orig_seq;
		temp[i] = (orig_seq[i] - '0' + 1) % 10 + '0';
		result.push_back(temp);
		temp[i] = (orig_seq[i] - '0' - 1 + 10) % 10 + '0';
		result.push_back(temp);
	}
	return result;
}

int min_helper(string &currVal, vector<string>& deadends, string& target) {
	//Base case
	if (currVal == target)
		return 0;
	
	//Check for dead end
	for (auto end : deadends) {
		if (currVal == end)
			return -1*std::numeric_limits<int>::infinity();
	}

	vector<string> steps = single_turn_seqs(currVal);
	int min = std::numeric_limits<int>::infinity();

	for (auto i : steps) {
		min = max(min, min_helper(currVal, deadends, target));
	}

	return 1 + min;
}

int min_turns_to_open_lock(vector<string>& deadends, string& target) {
	string s1("0000");
	int final = min_helper(s1, deadends, target);
	return final != numeric_limits<int>::infinity() ? final : -1;
}

int main() {
	vector<string> deadends = { "0201", "0101", "0102", "1212", "2002" };
	string target = "0202";
	cout << min_turns_to_open_lock(deadends, target) << endl;
}