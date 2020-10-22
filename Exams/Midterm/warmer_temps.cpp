#include <vector>
using namespace std;

vector<int> warmer_temperatures(vector<int>& temps) {
	vector<int> res(temps.size());
	for (int i = int(temps.size()) - 1; i >= 0; --i) {
		int j = i + 1;
		while (j < temps.size() && temps[j] <= temps[i]) {
			if (res[j] > 0)
				j = res[j] + j;
			else
				j = temps.size();
		}
		if (j < temps.size())
			res[i] = j - i;
	}
	return res;
}

int main() {
	vector<int> test = { 55,62,46,53,51,50,51,53,63 };
	warmer_temperatures(test);
}