struct Log {
	int timestamp;
	int id_A;
	int id_B;
};
#include <algorithm>
#include <vector>
using namespace std;

int find(vector<int> vec, int target, int compress) {
	if (compress != -1 && compress != vec[target]) {
		int next = vec[target];
		vec[target] = compress;
		find(vec, vec[next], compress);
	}
	return vec[target] = target ? target : find(vec, vec[target], -1);
}

int earliest_acquaintance(vector<Log>& friendships, int num_students) {
	int sum_students = (num_students * (num_students + 1)) / 2;
	vector<int> connections(num_students);
	for (int i = 0; i < connections.size(); i++) {
		connections[i] = i;
	}
	sort(friendships.begin(), friendships.end(), [](Log a, Log b) { return a.timestamp < b.timestamp; });
	int i = 0;
	for (; i < friendships.size() && sum_students != 0; i++) {
		int r1 = find(connections, friendships[i].id_A, -1), r2 = find(connections, friendships[i].id_B, -1);
		if (r1 < r2) {
			sum_students -= r2;
			connections[r2] = r1;
			find(connections, friendships[i].id_B, r1);
		}
		else if (r2 < r1) {
			sum_students -= r1;
			connections[r1] = r2;
			find(connections, friendships[i].id_A, r2);
		}
	}
	return sum_students == 0 ? -1 : friendships[i].timestamp;
}