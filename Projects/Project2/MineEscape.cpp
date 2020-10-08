// Project Identifier: 19034C8F3B1196BF8E0C6E1C0F973D2FD550B88F

#include <iostream>
#include <vector>
#include <getopt.h>
#include <deque>
#include <queue>
#include "P2random.h"

using namespace std;

struct tile {
public:

    tile() : rubble{ 0 }, row{ 0 }, col{ 0 }{}

    tile(int rubble_in, unsigned row_in, unsigned int col_in) :
        rubble{ rubble_in }, row{ row_in }, col{ col_in }{}

    int rubble;
    unsigned int row;
    unsigned int col;

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
        else if (a.row > b.col)
            return true;
        else
            return false;
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

    void discover(const tile &, priority_queue<tile, vector<tile>, tileComp> &);

    bool edge(const tile &);

    void setEdge(int row, int col);

private:

    //Underlying Data Structures
	vector<vector<tile>> layout;
    priority_queue<tile, vector<tile>, tileComp> primaryQueue;
    priority_queue<tile, vector<tile>, tileComp> TNTQueue;

    //Initial Variables
    pair<unsigned int, unsigned int> start = { 0,0 };

    //Command Line Args
    int firstCleared = -1;
    bool median = false;
    bool verbose = false;
    tile finalEdge;
    

};

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
            median = true;
            break;

        case 'v':
            verbose = true;
            break;

        case 'h':
            std::cerr << "This program reads in a mine from a file.\n"
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
    layout.resize(stoi(in), vector<tile>(stoi(in)));
    cin >> dump;
    cin >> in;

    start.first = stoi(in);
    //Check if start point is out of range
    if (start.first >= layout.size()) {
        cerr << "Invalid starting row\n";
        exit(1);
    }

    cin >> in;
    start.second = stoi(in);
    if (start.second > layout.size()) {
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

    for (unsigned int i = 0; i < layout.size(); ++i) {
        for (unsigned int j = 0; j < layout.size(); ++j) {        
            inputStream >> intermediate;
            layout[i][j].rubble = stoi(intermediate);
            layout[i][j].row = i;
            layout[i][j].col = j;
        }
    }

}

void mine::writeMine() {
    for (unsigned int i = 0; i < layout.size(); ++i) {
        for (unsigned int j = 0; j < layout.size(); ++j) {
            cout << layout[i][j].rubble << " ";
        }
        cout << "\n";
    }
}


bool mine::edge(const tile& current) {
    if (current.col != 0 && current.row != 0 &&
        current.col != layout.size() && current.row != layout.size())
        return false;
    return true;
}

void mine::setEdge(int row, int col) {
    if (finalEdge.rubble != -3) return;
    finalEdge.rubble = -4;
    finalEdge.row = row;
    finalEdge.col = col;
}

void mine::discover(const tile& current, priority_queue<tile, vector<tile>, tileComp>& pq) {
    unsigned int row = current.row;
    unsigned int col = current.col;

    if (row != 0) {
        if (layout[row - 1][col].rubble != -2)
            pq.push(layout[current.row - 1][current.col]);
    }
    else
        setEdge(row, col);
    if (row != layout.size()-1) {
        if (layout[row + 1][col].rubble != -2)
            pq.push(layout[current.row + 1][current.col]);
    }
    else
        setEdge(row, col);
    if (col != 0) {
        if (layout[row][col - 1].rubble != -2)
            pq.push(layout[current.row][current.col - 1]);
     }
    else
        setEdge(row, col);
    if (col != layout.size()-1) {
        if (layout[row][col + 1].rubble != -2)
            pq.push(layout[current.row][current.col + 1]);
    }
    else
        setEdge(row, col);

}

void mine::breakout() {
    
    //Initialize queue
    primaryQueue.push(layout[start.first][start.second]);
    tile current = primaryQueue.top();
    finalEdge.rubble = -3;

    //Loop through queue until edge is reached
    while (finalEdge.rubble == -3) {
        current = primaryQueue.top();

        //Check if TNT
        if (current.rubble == -1) {
            
            tile top = current;
            TNTQueue.push(top);

            //While TNT Queue is not Empty
            while (!TNTQueue.empty()) {
                top = TNTQueue.top();

                //Check if TNT
                if (top.rubble == -1) {
                    cout << "TNT explosion at [" << top.row << "," << top.col << "]!\n";
                    discover(top, TNTQueue);
                    layout[top.row][top.col].rubble = -2;
                    TNTQueue.pop();
                }

                //If not TNT Surroundings to Main Queue
                else {
                    if(top.rubble != 0)
                        cout << "Cleared by TNT: " << top.rubble << " at [" << top.row << "," << top.col << "]\n";
                    TNTQueue.pop();
                    discover(top, primaryQueue);
                    layout[top.row][top.col].rubble = -2;
                }

            }
        }

        //If not TNT then just clear it
        else {
            cout << "Cleared " << current.rubble << " at [" << current.row << "," << current.col << "]\n";
            primaryQueue.pop();
            discover(current, primaryQueue);
            layout[current.row][current.col].rubble = -2;
        }
    }

}

int main(int argc, char** argv) {
	mine jellystone;
	jellystone.get_options(argc, argv);
    jellystone.readMine();
    jellystone.breakout();
}
