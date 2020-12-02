/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *  EECS 281 Lab 9 - Number of Islands                     *
 *  Identifier: 472D3C8289DE4915774A47683EC45FFBA373B980   *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
 
#include "islands.h"

/*
 *  This program takes in an input file of the form:
 * 
 *  <num_rows>
 *    <map>
 *     ...
 */
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::string str;
    getline(std::cin, str);
    while (!str.empty() && str.front() == '#') {
        getline(std::cin, str);
    }
    uint32_t num_rows = (uint32_t)stoul(str);
    std::vector<std::vector<char>> grid(num_rows);
    for (uint32_t i = 0; i < num_rows; ++i) {
        getline(std::cin, str);
        std::istringstream iss(str);
        grid[i].assign(std::istream_iterator<char>(iss), std::istream_iterator<char>());
    }
    std::cout << "Your solution: " << number_of_islands(grid) << std::endl;
    return 0;
}