// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "PathFinder.hpp"

void PathFinder::read() {

	string curr = "";

	cin >> curr;
	int size = stoi(curr);

	//Resize all vectors
	m_vertexes.resize(size);
	m_minEdges.resize(size, std::numeric_limits<double>::infinity());
	m_preVertex.resize(size);
	m_visited.resize(size);

}