// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "PathFinder.hpp"

PathFinder::PathFinder() {
	//Initialize stuff
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
		
		Point::Location loc = Point::Location::ship;
		cin >> x;
		cin >> y;
		xi = stoi(x);
		yi = stoi(y);
		
		//Lab Check
		if (xi < 0 && yi < 0) {
			loc = Point::Location::lab;
			
			if (!lab)
				lab = true;
		}

		//Decontamination Check
		if ((xi <= 0 && yi == 0) || (xi == 0 && yi <= 0)) {
			loc = Point::Location::decontamination;
			if (!decontam)
				decontam = true;
		}
		
		//Ship Check
		if (!ship && loc == Point::Location::ship)
			ship = true;

		m_vertices[i] = Point{ stoi(x), stoi(y), loc };
	}

	if (ship && lab && !decontam) {
		cerr << "Cannot construct MST\n";
		exit(1);
	}
}