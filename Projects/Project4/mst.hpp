// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#pragma once
#include "PathFinder.hpp"

using namespace std;

class MST : public PathFinder {

public:
	//Default Constructor
	MST() {}

	//Finds distance between two points
	double findDistance(const size_t, const size_t);

	//Executes the MST Algorithm
	void run();

	//Prints MST Output
	void print();
};