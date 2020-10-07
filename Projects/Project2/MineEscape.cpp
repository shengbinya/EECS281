// Project Identifier: 19034C8F3B1196BF8E0C6E1C0F973D2FD550B88F

#include <iostream>
#include <vector>
#include <getopt.h>
#include <deque>
#include <queue>
#include "P2random.h"

using namespace std;

class mine {
private:
    //Underlying Data Structures
	vector<vector<int>> mine;

    //Initial Variables
    pair<unsigned int, unsigned int> start = { 0,0 };

    //Command Line Args
    int firstCleared = -1;
    bool median = false;
    bool verbose = false;
    
public:
    //Grabs options from command line
    void get_options(int argc, char** argv);

	//Reads in input from file
	void readMine();

    //Write out mine in command line
    void writeMine();
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
    mine.resize(stoi(in), vector<int>(stoi(in)));
    cin >> dump;
    cin >> in;

    start.first = stoi(in);
    //Check if start point is out of range
    if (start.first >= mine.size()) {
        cerr << "Invalid starting row\n";
        exit(1);
    }

    cin >> in;
    start.second = stoi(in);
    if (start.second > mine.size()) {
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

    for (unsigned int i = 0; i < mine.size(); ++i) {
        for (unsigned int j = 0; j < mine.size(); ++j) {        
            inputStream >> intermediate;
            mine.at(j).at(i) = stoi(intermediate);
        }
    }

}

void mine::writeMine() {
    for (unsigned int i = 0; i < mine.size(); ++i) {
        for (unsigned int j = 0; j < mine.size(); ++j) {
            cout << mine[j][i] << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char** argv) {
	mine jellystone;
	jellystone.get_options(argc, argv);
    jellystone.readMine();
    jellystone.writeMine();


}