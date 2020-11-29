// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <unordered_map>
#include <exception>
#include <algorithm>
#include <string>
#include "getopt.h"

using namespace std;

struct Point{
	double x;
	double y;
};

class MST {

private:
	vector<Point> m_vertices;
	vector<double> m_minEdges;
	vector<int> m_preVertex;
	vector<bool> m_visited;

public:
	//Default Constructor
	MST() {}

	//Reads in data from command line
	void read();

	//Prints MST Output
	void print();
};