// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "MST.hpp"
#include <string.h>

using namespace std;

int getOptions(int argc, char** argv) {
	int option_index = 0, option = 0;

	int choice = 0;

	// Don't display getopt error messages about options
	opterr = false;

	// use getopt to find command line options
	struct option longOpts[] = { { "mode", required_argument, nullptr, 'm' },
								{ "help", no_argument, nullptr, 'h'},
								{ nullptr, 0, nullptr, '\0' } };

	while ((option = getopt_long(argc, argv, "m:h", longOpts, &option_index)) != -1) {
		switch (option) {
		case 'm':
			if (strcmp(optarg,"MST") == 0)
				choice = 1;
			else if (strcmp(optarg, "FASTTSP") == 0)
				choice = 2;
			else if (strcmp(optarg, "OPTTSP") == 0)
				choice = 3;
			else {
				cout << "Invalid Argument: " << optarg << "\n";
				exit(1);
			}
			break;

		case 'h':
			cout << "This program reads in user input from command line and calculates"
				<< " the shortest path to all points in various scenarios.\n"
				<< "Usage: \'./amongus\n\t[--mode | -m]\n"
				<< "\t[--help | -h]\n";
			exit(1);
		}
	}
	return choice;
}

int main(int argc, char** argv) {
	
	std::ios_base::sync_with_stdio(false);
	cout << std::setprecision(2); //Always show 2 decimal places
	cout << std::fixed; //Disable scientific notation for large numbers


	int choice = getOptions(argc, argv);

	//MST Option
	if (choice == 1) {
		MST mst;
		mst.run();
		mst.print();
	}
}