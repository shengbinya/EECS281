#include <iostream>
void print_an_integer(int x) { std::cout << x; }
int main() {
	size_t x;
	std::cin >> x;
	print_an_integer(x);
}