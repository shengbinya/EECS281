int sum_remnant_values(const std::vector<int>& seq, int k) {
	deque<int> consecutive;
	vector<int> final;
	int curr_consecutive = 0, num = 0;
	for (int i = 0; i < seq.size() - 1; i++) {
		consecutive.push_front(seq[i]);
		if (seq[i + 1] == seq[i]) {
			curr_consecutive++;
		}
		else if (curr_consecutive >= k) {
			for (int comp = seq[i]; consecutive.front() == comp; curr_consecutive = 0) {
				consecutive.pop_front();
			}
		}
		else {
			for (; curr_consecutive < consecutive.size() && consecutive[curr_consecutive] == seq[i]; curr_consecutive++) {
				if (curr_consecutive > k) {
					curr_consecutive = -1;
					break;
				}
				if (curr_consecutive == -1) {
					for (int comp = seq[i]; consecutive.front() == comp; curr_consecutive = 0) {
						consecutive.pop_front();
					}
				}
			}
		}
	}
	
	while (!consecutive.empty()) {
		num += consecutive.front();
		consecutive.pop_front();
	}
	return num;
}