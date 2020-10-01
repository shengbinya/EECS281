#include "String.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>


int main() {
	String fish = "corn";
	fish.erase(1, 2);
	for (size_t i = 0; i < fish.size(); ++i) {
		std::cout << fish[i];
	}
}