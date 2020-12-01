// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#pragma once
#include "PathFinder.hpp"

using namespace std;

struct PointLoc {
	//Enumerated Location Type
	enum Location { lab, decontamination, ship };
	int x;
	int y;
	Location loc;
};

class MST : public PathFinder {

private:
	vector<PointLoc> m_vertices;
	vector<double> m_minEdges;
	vector<int> m_preVertex;
	vector<bool> m_visited;

public:

	//Default Constructor
	MST() {}

	//Finds distance between two points
	double findDistance(const size_t, const size_t) override;

	//Read function
	void read() override;
	
	//Executes the MST Algorithm
	void run() override;

	void print() override;
};