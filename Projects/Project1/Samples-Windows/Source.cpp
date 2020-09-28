#include <iostream>
#include <string>
 
using namespace std;


int main() {
	cout << "S" << "\n";
	cout << "400\n";
	for (int j = 1; j < 401; ++j) {
		for (int i = 0; i < j; i++) {
			cout << "a";
		}
		cout << "\n";
	}
	

}