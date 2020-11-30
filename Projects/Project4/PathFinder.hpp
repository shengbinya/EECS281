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
#include <cmath>
#include <iomanip>
#include "getopt.h"

using namespace std;

struct Point {
	
	int x;
	int y;
	
};

class PathFinder {

public:
	
	//Variable Declarations
	vector<Point> m_vertexes;
	vector<double> m_minEdges;
	vector<int> m_preVertex;
	vector<bool> m_visited;

	//Default Constructor
	PathFinder() {}

	virtual void read();
};