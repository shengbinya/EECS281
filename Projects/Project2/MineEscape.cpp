// Project Identifier: 19034C8F3B1196BF8E0C6E1C0F973D2FD550B88F

#include <iostream>
#include <vector>
#include <getopt.h>
#include <deque>
#include <queue>
#include "P2random.h"

using namespace std;

class tile {
public:

    tile() : rubble{ 0 }, row{ 0 }, col{ 0 }{}

    tile(unsigned rubble_in, unsigned row_in, unsigned int col_in) :
        rubble{ rubble_in }, row{ row_in }, col{ col_in }{}

    bool operator()(const tile& a, const tile& b) {
        if (a.rubble < b.rubble)
            return true;
        else if (a.rubble > b.rubble)
            return false;
        else if (a.col < b.col)
            return true;
        else if (a.col > b.col)
            return false;
        else if (a.row < b.col)
            return true;
        else
            return false;
    }

    int rubble;
    unsigned int row;
    unsigned int col;

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

    void clear(const tile &);

    void clearTNT();

private:

    //Underlying Data Structures
	vector<vector<tile>> layout;
    priority_queue<tile, vector<tile>> primaryQueue;

    //Initial Variables
    pair<unsigned int, unsigned int> start = { 0,0 };

    //Command Line Args
    int firstCleared = -1;
    bool median = false;
    bool verbose = false;
    

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
            layout[j][i].rubble = stoi(intermediate);
            layout[j][i].row = j;
            layout[j][i].col = i;
        }
    }

}

void mine::writeMine() {
    for (unsigned int i = 0; i < layout.size(); ++i) {
        for (unsigned int j = 0; j < layout.size(); ++j) {
            cout << layout[j][i].rubble << " ";
        }
        cout << "\n";
    }
}

void mine::clear(const tile &tile) {
    //Check if edge has been reached
    if (tile.row == layout.size() || tile.col == layout.size()) {

    }

    //Check if TNT
    if (tile.rubble == -1)
        clearTNT();
    
    //Discover 4 corners
    else {
        primaryQueue.push(layout[tile.row + 1][tile.col + 1]);
    }
}

void mine::breakout() {
    

}

int main(int argc, char** argv) {
	mine jellystone;
	jellystone.get_options(argc, argv);
    jellystone.readMine();
    jellystone.writeMine();


}