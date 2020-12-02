/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *  EECS 281 Lab 9 - Number of Islands                     *
 *  Identifier: 472D3C8289DE4915774A47683EC45FFBA373B980   *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ISLANDS_H
#define ISLANDS_H

#include <vector>
#include <deque>

using namespace std;

int number_of_islands(std::vector<std::vector<char>>& grid) {
    
    deque<pair<int, int>> search;
    int numIslands = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++i) {
            if (grid[i][j] == 'o') {
                //Initialize the stack
                search.push_front(pair<int, int>{ i,j });
                ++numIslands;

                //Investigate and add points
                while (!search.empty()) {
                    
                    //Pull off the front and investigate
                    pair<int, int> curr = search.front();
                    grid[curr.first][curr.second] = '.';
                    search.pop_front();
                    
                    //Check point above current point
                    if (curr.first != 0 && grid[curr.first - 1][curr.second] == 'o')
                        search.push_front(pair<int, int>{curr.first-1, curr.second});

                    //Check point below current point
                    if (curr.first != grid.size() && grid[curr.first + 1][curr.second] == 'o')
                        search.push_front(pair<int, int>{curr.first+1, curr.second});

                    //Check point to right of current
                    if (curr.second != grid[i].size() && grid[curr.first][curr.second+1] == 'o')
                        search.push_front(pair<int, int>{curr.first, curr.second+1});

                    //Check point to left of current
                    if (curr.second != 0 && grid[curr.first][curr.second - 1] == 'o')
                        search.push_front(pair<int, int>{curr.first, curr.second - 1});

                }
            }
        }
    }

    return numIslands;
    
}

#endif /* ISLANDS_H */
