#include "PathFinder.hpp"

PathFinder::PathFinder() {
	//Initialize stuff
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
		if (xi < 0 && yi < 0)
			loc = Point::Location::lab;

		//Decontamination Check
		if ((xi <= 0 && yi == 0) || (xi == 0 && yi <= 0))
			loc = Point::Location::decontamination;
		
		m_vertices[i] = Point{ stoi(x), stoi(y), loc };
	}
}