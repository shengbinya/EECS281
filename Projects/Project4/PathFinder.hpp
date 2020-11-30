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
	//Enumerated Location Type
	enum Location { lab, decontamination, ship };

	int x;
	int y;
	Location loc;
	
};

class PathFinder {

public:
	
	//Variable Declarations
	vector<Point> m_vertices;
	vector<double> m_minEdges;
	vector<int> m_preVertex;
	vector<bool> m_visited;

	//Default Constructor
	PathFinder();

};