// Project Identifier: 19034C8F3B1196BF8E0C6E1C0F973D2FD550B88F

#include <iostream>
#include <vector>
#include <getopt.h>
#include <deque>
#include <queue>
#include "P2random.h"
#include <set>
#include <iomanip>

using namespace std;

struct tile {
public:

    tile() : rubble{ 0 }, row{ 0 }, col{ 0 }{}

    tile(int rubble_in, unsigned row_in, unsigned int col_in) :
        rubble{ rubble_in }, row{ row_in }, col{ col_in }{}

    int rubble;
    unsigned int row;
    unsigned int col;
    bool discovered = false;

};

struct tileComp {
    bool operator()(const tile& a, const tile& b) {
        if (a.rubble > b.rubble)
            return true;
        else if (a.rubble < b.rubble)
            return false;
        else if (a.col > b.col)
            return true;
        else if (a.col < b.col)
            return false;
        else if (a.row > b.row)
            return true;
        else
            return false;
    }
};

struct tileCompOp {
    bool operator()(const tile& a, const tile& b) {
        if (a.rubble < b.rubble)
            return true;
        else if (a.rubble > b.rubble)
            return false;
        else if (a.col < b.col)
            return true;
        else if (a.col > b.col)
            return false;
        else if (a.row < b.row)
            return true;
        else
            return false;
    }
};

struct intCompLess {
    bool operator()(int a, int b) {
        return a > b;
    }
};

class mine {
public:

    //Grabs options from command line
    void get_options(int argc, char** argv);

    //Reads in input from file
    void readMine();

    //Write out mine in command line
    void writeMine();

    void breakout();

    void discover(const tile&);

    void setEdge(int row, int col);

    void printMedian();

    void printStats();

    void blowUp(const tile& current);

    void addMedian(int);

private:

    //Underlying Data Structures
    vector<vector<tile>> gridMine;
    
    priority_queue<tile, vector<tile>, tileComp> primaryQueue;
    priority_queue<tile, vector<tile>, tileComp> TNTQueue;
    
    priority_queue<int, vector<int>> leftPQ;
    priority_queue<int, vector<int>,intCompLess> rightPQ;
    
    vector<tile> discard;

    //Initial Variables
    pair<unsigned int, unsigned int> start = { 0,0 };
    unsigned int totalRubble = 0;
    unsigned int totalTiles = 0;

    //Command Line Args
    int firstCleared = -1;
    bool m = false;
    bool v = false;
    tile finalEdge {-3, 0, 0};
    

};

//Definitions:
//If something is "cleared" the rubble value is set to 0
//If something is "discovered" the discovered variable is set to true
//If something is "investigated" the discovered variable is true and the rubble value is 0

/* Helper Functions*/

void mine::writeMine() {
    for (unsigned int i = 0; i < gridMine.size(); ++i) {
        for (unsigned int j = 0; j < gridMine.size(); ++j) {
            cout << gridMine[i][j].rubble << " ";
        }
        cout << "\n";
    }
}

void mine::printStats() {

    cout << "First tiles cleared:\n";
    for (int i = 0; i < firstCleared && i < int(discard.size()); i++) {
        if (discard[i].rubble != -1)
            cout << discard[i].rubble << " at [" << discard[i].row << "," << discard[i].col << "]\n";
        else
            cout << "TNT at [" << discard[i].row << "," << discard[i].col << "]\n";
    }

    cout << "Last tiles cleared:\n";
    for (int i = int(discard.size()) - 1; i > int(discard.size()) - firstCleared -1 && i > -1; --i) {
        if (discard[i].rubble != -1)
            cout << discard[i].rubble << " at [" << discard[i].row << "," << discard[i].col << "]\n";
        else
            cout << "TNT at [" << discard[i].row << "," << discard[i].col << "]\n";
    }

    priority_queue<tile, vector<tile>, tileComp> statsQueue(discard.begin(), discard.end());
    cout << "Easiest tiles cleared:\n";
    for (int i = 0; i < firstCleared && i < int(discard.size()); i++) {
        if (statsQueue.top().rubble != -1)
            cout << statsQueue.top().rubble << " at [" << statsQueue.top().row << "," << statsQueue.top().col << "]\n";
        else
            cout << "TNT at [" << statsQueue.top().row << "," << statsQueue.top().col << "]\n";
        statsQueue.pop();
    }

    priority_queue<tile, vector<tile>, tileCompOp> statsQueueBack(discard.begin(), discard.end());
    cout << "Hardest tiles cleared:\n";
    for (int i = 0; i < firstCleared && i < int(discard.size()); i++) {
        if (statsQueueBack.top().rubble != -1)
            cout << statsQueueBack.top().rubble << " at [" << statsQueueBack.top().row << "," << statsQueueBack.top().col << "]\n";
        else
            cout << "TNT at [" << statsQueueBack.top().row << "," << statsQueueBack.top().col << "]\n";
        statsQueueBack.pop();
    }


}

void mine::setEdge(int row, int col) {
    if (finalEdge.rubble != -3) return;
    finalEdge.rubble = -4;
    finalEdge.row = row;
    finalEdge.col = col;
    finalEdge.discovered = true;
}

void mine::blowUp(const tile& current) {
    unsigned int row = current.row;
    unsigned int col = current.col;

    //If not in top row
    if (row != 0) {
        if (gridMine[row - 1][col].rubble != 0) {
            TNTQueue.push(gridMine[row - 1][col]);
            //Clear here to indicate that it has already been blown up
            gridMine[row - 1][col].rubble = 0;
        }
    }
    else
        setEdge(row, col);

    //If not in bottom row
    if (row != gridMine.size() - 1 ) {
        if (gridMine[row + 1][col].rubble != 0) {
            TNTQueue.push(gridMine[row + 1][col]);
            gridMine[row + 1][col].rubble = 0;
        }
    }
    else
        setEdge(row, col);

    //If not on left edge
    if (col != 0) {
        if (gridMine[row][col - 1].rubble != 0) {
            TNTQueue.push(gridMine[row][col - 1]);
            gridMine[row][col - 1].rubble = 0;
        }
    }
    else
        setEdge(row, col);

    //If not on bottom edge
    if (col != gridMine.size() - 1){
        if (gridMine[row][col + 1].rubble != 0) {
            TNTQueue.push(gridMine[row][col + 1]);
            gridMine[row][col + 1].rubble = 0;
        }
    }
    else
        setEdge(row, col);
}

void mine::discover(const tile& current) {
    unsigned int row = current.row;
    unsigned int col = current.col;

    //If not on upper edge
    if (row != 0) {
        //If not already discovered
        if (!gridMine[current.row - 1][current.col].discovered) {
            primaryQueue.push(gridMine[current.row - 1][current.col]);
            gridMine[current.row - 1][current.col].discovered = true;
        }
            
    }
    else
        setEdge(row, col);

    //If not on lower edge
    if (row != gridMine.size() - 1) {
        //If not already discovered
        if (!gridMine[current.row + 1][current.col].discovered) {
            primaryQueue.push(gridMine[current.row + 1][current.col]);
            gridMine[current.row + 1][current.col].discovered = true;
        }
            
    }
    else
        setEdge(row, col);

    //If not on left edge
    if (col != 0) {
        //If not already discovered
        if (!gridMine[row][col - 1].discovered) {
            primaryQueue.push(gridMine[row][col - 1]);
            gridMine[row][col - 1].discovered = true;
        }
            
    }
    else
        setEdge(row, col);

    //If not on right edge
    if (col != gridMine.size() - 1) {
        //If not already discovered
        if (!gridMine[row][col + 1].discovered) {
            primaryQueue.push(gridMine[row][col + 1]);
            gridMine[row][col + 1].discovered = true;
        }   
    }
    else
        setEdge(row, col);

}

void mine::addMedian(int a) {

    //Always want left to be one larger or equal to right side
    
    //Need to push left
    if (leftPQ.size() == rightPQ.size()) {
        
        //If less than or equal to largest left side it belongs in left side
        if (leftPQ.empty() || a <= rightPQ.top())
            leftPQ.push(a);
        
        //If greater than largest left it belongs in the right side
        else {
            int temp = rightPQ.top();
            rightPQ.pop();
            rightPQ.push(a);
            leftPQ.push(temp);
        }
    }

    //Push right
    else {

        //If right side is empty make sure it is larger than largest left without using .top()
        if (rightPQ.empty()) {
            
            if (leftPQ.top() <= a)
                rightPQ.push(a);
            else {
                int temp = leftPQ.top();
                leftPQ.pop();
                leftPQ.push(a);
                rightPQ.push(temp);
            }

        }

        //If greater than smallest value right side it belongs right side
        else if (a >= leftPQ.top())
            rightPQ.push(a);
        
        //If smaller than smallest element in the right side it belongs in left side
        else {
            int temp = leftPQ.top();
            leftPQ.pop();
            leftPQ.push(a);
            rightPQ.push(temp);
        }
    }

}

void mine::printMedian() {

    cout << "Median difficulty of clearing rubble is: ";
    cout << std::fixed << std::setprecision(2);
    int size = int(leftPQ.size() + rightPQ.size());

    //If even average
    if (size % 2 == 0 && (size % 2) != 1) {
        if (size != 1) {
            double step = leftPQ.top() + rightPQ.top();
            step = step / 2;
            cout << step << "\n";
        }
    }

    //If odd just return leftPQ value    
    else
        cout << double(leftPQ.top()) << "\n";
}

/* Main Functions */
void mine::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;

    // Don't display getopt error messages about options
    opterr = false;

    // use getopt to find command line options
    struct option longOpts[] = { { "stats", required_argument, nullptr, 's' },
                                { "median", no_argument, nullptr, 'm' },
                                { "verbose", no_argument, nullptr, 'v' },
                                { "help", no_argument, nullptr, 'h'},
                                { nullptr, 0, nullptr, '\0' } };

    while ((option = getopt_long(argc, argv, "s:mvh", longOpts, &option_index)) != -1) {
        switch (option) {
        case 's':
            firstCleared = atoi(optarg);
            break;

        case 'm':
            m = true;
            break;

        case 'v':
            v = true;
            break;

        case 'h':
           cout << "This program reads in a mine from a file.\n"
                << "It finds the easiest clear path through the mine\n"
                << "and can generate output to indicate this path\n"
                << "according to the provided arguemnts."
                << "Usage: \'./letter\n\t[--stack | -s]\n"
                << "\t[--stats | -s]\n"
                << "\t[--median | -m]\n"
                << "\t[--verbose | -v]\n"
                << "\t[--length | -l]\n"
                << "\t[--help | -h]\n"
                << "\t<Mine File>\'" << std::endl;
            exit(1);
        }
    }
}

void mine::readMine() {
    //Read in common variables
    string mode = "";
    string in = "";
    string dump = "";
    
    cin >> mode;
    //Check if mode is correct
    if (mode != "R" && mode != "M") {
        cerr << "Invalid input mode\n";
        exit(1);
    }

    cin >> dump;
    cin >> in;
    //Read in size
    unsigned int size = stoi(in);
    gridMine.resize(stoi(in), vector<tile>(stoi(in)));
    cin >> dump;
    cin >> in;

    start.first = stoi(in);
    //Check if start point is out of range
    if (start.first >= gridMine.size()) {
        cerr << "Invalid starting row\n";
        exit(1);
    }

    cin >> in;
    start.second = stoi(in);
    if (start.second > gridMine.size()) {
        cerr << "Invalid starting column\n";
        exit(1);
    }

    stringstream ss;
    if (mode == "R") {
        //Read in specifics
        cin >> dump;
        cin >> in;
        int seed = stoi(in);
        cin >> dump;
        cin >> in;
        unsigned int max_rubble = stoi(in);
        cin >> dump;
        cin >> in;
        unsigned int tnt_chance = stoi(in);
        P2random::PR_init(ss, size, seed, max_rubble, tnt_chance);
    }

    istream& inputStream = (mode == "M") ? cin : ss;

    string intermediate;

    for (unsigned int i = 0; i < gridMine.size(); ++i) {
        for (unsigned int j = 0; j < gridMine.size(); ++j) {        
            inputStream >> intermediate;
            gridMine[i][j].rubble = stoi(intermediate);
            gridMine[i][j].row = i;
            gridMine[i][j].col = j;
        }
    }

}

void mine::breakout() {
    
    //Initialize Primary Queue
    tile investigated (gridMine[start.first][start.second].rubble, start.first, start.second);
    investigated.discovered = true;
    primaryQueue.push(investigated);

    //Loop through primary queue discovering and investigating tiles
    while (finalEdge.rubble == -3) {

        //Grab top of primary queue and investigate it
        investigated = primaryQueue.top();
        primaryQueue.pop();
        
            //If not TNT the miner investigates
            if (gridMine[investigated.row][investigated.col].rubble != -1) {
               
                //If the actual tile is not equal to 0 we don't want to output stuff
                //We do want to discover around the tile
                if (gridMine[investigated.row][investigated.col].rubble != 0) {
                    
                    //Clear the actual tile
                    gridMine[investigated.row][investigated.col].rubble = 0;

                    //Statistics Updates
                    if (investigated.rubble != 0) {
                        if (v) {
                            std::cout << "Cleared: " << investigated.rubble << " at [" << investigated.row << "," << investigated.col << "]\n";
                        }
                        if (m) {
                            addMedian(investigated.rubble);
                            printMedian();
                        }
                        if (firstCleared != -1)
                            discard.push_back(investigated);

                        totalTiles++;
                        totalRubble += investigated.rubble;

                    }
                }

                //Discover tiles around the cleared tile
                discover(investigated);
       
            }

            //If TNT
            else {

                //Initialize TNT Queue
                TNTQueue.push(investigated);
                tile currentTNT;

                //Fire up TNT While loop
                while (!TNTQueue.empty()) {

                    //Add top of queue to current TNT
                    currentTNT = TNTQueue.top();
                    TNTQueue.pop();

                    //If TNT
                    if (currentTNT.rubble == -1) {

                        //Clear the TNT
                        gridMine[currentTNT.row][currentTNT.col].rubble = 0;
                        if (v)
                            std::cout << "TNT explosion at [" << currentTNT.row << "," << currentTNT.col << "]!\n";
                        if (firstCleared != -1)
                            discard.push_back(currentTNT);
                        //Add stuff around TNT to TNTQueue
                        blowUp(currentTNT);
                        
                        //Discover the tile for the primary queue
                        gridMine[currentTNT.row][currentTNT.col].discovered = 0;

                    }

                    //If not TNT clear and add to PQ for discovery
                    else {

                        //Statistics Updates
                        if (currentTNT.rubble != 0) {
                            if (v)
                                std::cout << "Cleared by TNT: " << currentTNT.rubble << " at [" << currentTNT.row << "," << currentTNT.col << "]\n";
                            if (m) {
                                addMedian(currentTNT.rubble);
                                printMedian();
                            }
                            if (firstCleared != -1)
                                discard.push_back(currentTNT);

                            totalTiles++;
                            totalRubble += currentTNT.rubble;
                        }
                      
                        //Discover tiles with 0 rubble for normal PQ
                        if (currentTNT.rubble == 0)
                            discover(currentTNT);
                        //Add Discovered TNT to queue to be investigated 
                        else
                            primaryQueue.push(gridMine[currentTNT.row][currentTNT.col]);

                    }
                }

            }

    }

    std::cout << "Cleared " << totalTiles << " tiles containing " << totalRubble << " rubble and escaped.\n";
    if (firstCleared != -1)
        printStats();
}


int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(2);
	mine jellystone;
	jellystone.get_options(argc, argv);
    jellystone.readMine();
    jellystone.breakout();
}