// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "MST.hpp"

using namespace std;

void MST::read() {
	
	//Initialize Stuff
	bool lab = false;
	bool decontam = false;
	bool ship = false;
	string x = "";
	string y = "";
	int xi = 0;
	int yi = 0;
	string curr = "";

	cin >> curr;
	int size = stoi(curr);

	//Resize all vectors
	m_vertices.resize(size);
	m_minEdges.resize(size, std::numeric_limits<double>::infinity());
	m_preVertex.resize(size);
	m_visited.resize(size);

	//Read in information
	for (int i = 0; i < size; i++) {

		PointLoc::Location loc = PointLoc::Location::ship;
		cin >> x;
		cin >> y;
		xi = stoi(x);
		yi = stoi(y);

		//Lab Check
		if (xi < 0 && yi < 0) {
			loc = PointLoc::Location::lab;

			if (!lab)
				lab = true;
		}

		//Decontamination Check
		if ((xi <= 0 && yi == 0) || (xi == 0 && yi <= 0)) {
			loc = PointLoc::Location::decontamination;
			if (!decontam)
				decontam = true;
		}

		//Ship Check
		if (!ship && loc == PointLoc::Location::ship)
			ship = true;

		m_vertices[i] = PointLoc{ xi, yi, loc };
	}

	if (ship && lab && !decontam) {
		cerr << "Cannot construct MST\n";
		exit(1);
	}
}

double MST::findDistance(const size_t t_i, const size_t t_j) {
	PointLoc* i = &m_vertices[t_i];
	PointLoc* j = &m_vertices[t_j];

	//If not reachable send infinity
	if ((i->loc == PointLoc::Location::lab && j->loc == PointLoc::Location::ship) ||
		(i->loc == PointLoc::Location::ship && j->loc == PointLoc::Location::lab))
		return std::numeric_limits<double>::infinity();
	else {
		double xdiff = i->x - j->x;
		double ydiff = i->y - j->y;
		return sqrt(xdiff * xdiff + ydiff * ydiff);
	}
}

void MST::run() {
	int currSmallest = 0;
	double edgeTotal = 0;
	//Iterate over each point
	for (size_t i = 0; i < m_vertices.size(); i++) {
		int nextSmallest = -1;
		
		//Check connection between each point and all other points
		for (size_t j = 0; j < m_vertices.size(); j++) {
			
			//If not visited find the distance
			if (!m_visited[j]) {
				//If uninitialized set = to j
				if (nextSmallest == -1)
					nextSmallest = (int)j;

				double dist = findDistance(currSmallest, j);
				
				//If found distance is smaller than the current distance
				if (dist < m_minEdges[j]) {
					m_minEdges[j] = dist; //Set min edge distance
					m_preVertex[j] = currSmallest;   //Define vertex with min edge
				}//if
				
				//Check if smallest edge
				if (m_minEdges[j] < m_minEdges[nextSmallest])
					nextSmallest = (int)j;
			}//if

		}//for

		//Smallest in iteration has been found reset for next step
		m_visited[nextSmallest] = true;
		currSmallest = nextSmallest;
		edgeTotal += m_minEdges[currSmallest];
	
	}//for
	cout << edgeTotal << "\n";
}

void MST::print() {
	//Skip initial squence
	for (size_t i = 1; i < m_preVertex.size(); ++i) {
		//Print smaller then larger
		cout << (i < (size_t)m_preVertex[i] ? i : m_preVertex[i]);
		cout << " " << (i < (size_t)m_preVertex[i] ? m_preVertex[i] : i) << "\n";
	}
}