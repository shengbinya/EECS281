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
	
	virtual void read() = 0;

	virtual void print() = 0;

	virtual void run() = 0;

	virtual double findDistance(const size_t, const size_t) = 0;

};