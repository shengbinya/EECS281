// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "mst.hpp"

using namespace std;

void MST::read() {

	string x = "";
	string y = "";
	string curr = "";

	cin >> curr;
	int size = stoi(curr);
	
	//Resize all vectors
	m_vertices.resize(size);
	m_minEdges.resize(size);
	m_preVertex.resize(size);
	m_visited.resize(size);

	for (int i = 0; i < size; i++) {
		cin >> x;
		cin >> y;
		m_vertices[i] = Point{ stod(x), stod(y) };
	}
}

void MST::print() {
	for (auto const &i : m_vertices) {
		cout << i.x << " " << i.y << "\n";
	}
}