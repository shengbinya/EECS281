// Testing file provided for EECS 281 Lab 7

#include "hashtable.h"
#include <string>
#include <iostream>

int main() {

    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)
    HashTable<std::string, int> midterm;
    midterm["a"] = 1;
    midterm["K"] = 2;
    std::cout << (midterm["AAA"] = 6) << "\n";

    std::cout << midterm.insert("sam", 50) << " ";
    std::cout << midterm.insert("fee", 100) << " ";
    std::cout << midterm.insert("milo", 95) << " ";
    std::cout << midterm.size() << "\n";
    std::cout << midterm.insert("gabe", 88) << " \n";
    midterm.insert("fish", 77);
    midterm.insert("fish1", 80);
    midterm.insert("zax", 90);
    midterm.insert("grabe", 10);
    std::cout << midterm.size() << "\n";
    std::cout << midterm["sam"] << " ";
    std::cout << midterm["fee"] << " ";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm["gabe"] << " \n";
    std::cout << midterm.erase("sam") << " ";
    std::cout << midterm.erase("fee") << " ";
    std::cout << midterm.erase("zax") << " ";
    std::cout << midterm.erase("fish1123") << " ";
    std::cout << midterm["sam"] << "\n";
    std::cout << midterm["zax"] << "\n";
    std::cout << midterm.size() << "\n";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm.size() << "\n";
    std::cout << midterm.size() << "\n";
    // ADD MORE TESTS OF YOUR OWN

    return 0;
}
