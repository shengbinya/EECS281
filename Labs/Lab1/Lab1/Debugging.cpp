#include <vector>
int *get_some_ints() {
	std::vector<int> ints = { 1,2,3,4,5};
	return ints.data();
}
int main() {
	int* some_ints = get_some_ints();
	delete[] some_ints;
	return 0;
}