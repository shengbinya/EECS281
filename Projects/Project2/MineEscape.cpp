// Project Identifier: 19034C8F3B1196BF8E0C6E1C0F973D2FD550B88F

#include <iostream>
#include <vector>
#include <getopt.h>
#include <deque>
#include <queue>

using namespace std;

class mine {
private:
    //Underlying Data Structures
	vector<vector<int>> mine;
    
    //Command Line Args
    int firstCleared = -1;
    bool median = false;
    bool verbose = false;
    
public:
	//Reads in input from file
	//void readMine();

	//Grabs options from command line
	void get_options(int argc, char** argv);

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

int main(int argc, char** argv) {
	mine jellystone;
	jellystone.get_options(argc, argv);
    
}