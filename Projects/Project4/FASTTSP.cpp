// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "FASTTSP.hpp"

void FASTTSP::read() {
	//Initialize Stuff
	string x = "";
	string y = "";
	string curr = "";

	cin >> curr;
	int size = stoi(curr);

	//Resize all vectors
	m_vertices.resize(size);
	m_path.reserve(size);
	
	//Read in information
	for (int i = 0; i < size; i++) {

		cin >> x;
		cin >> y;;

		m_vertices[i] = Point{ stoi(x), stoi(y) };
	}
}

double FASTTSP::findDistance(const size_t t_i, const size_t t_j) {
	Point* i = &m_vertices[t_i];
	Point* j = &m_vertices[t_j];

	double xdiff = i->x - j->x;
	double ydiff = i->y - j->y;
	return sqrt(xdiff * xdiff + ydiff * ydiff);
}

void FASTTSP::run() {
	//Add first cycle
	double dist = findDistance(0, 1);
	m_path.push_back(pair<int, double>{ 0, dist });
	m_path.push_back(pair<int, double>{ 1, dist });
	double totalDist = 2*dist;

	//Add points to cycle in order of insertion
	for (size_t i = 2; i < m_vertices.size(); ++i) {

		//Distance of minimal insertion between two adjacent vertices
		double minDist = std::numeric_limits<double>::infinity();
		int minIndex = -1; //First adjacent vertice with min dist

		//Find two adjacent points where distance is a min
		for (size_t j = 0; j < m_path.size() - 1; j++) {
			double currDist = findDistance(i, m_path[j].first) + findDistance(i, m_path[j + 1].first) - m_path[j].second;
			if (currDist < minDist) {
				minDist = currDist;
				minIndex = (int)j;
			}
		}

		//Add point between the two smaller points
		
		//Find new Distances
		double newDistL = findDistance(i, m_path[minIndex].first);
		double newDistR = findDistance(i, m_path[minIndex + 1].first);
		
		//Update points and insert
		totalDist -= m_path[minIndex].second;
		m_path[minIndex].second = newDistL;
		m_path.insert(m_path.begin()+minIndex + 1, pair<int, double>{i, newDistR});
		totalDist += newDistL + newDistR;
	}

	cout << totalDist << "\n";
}

void FASTTSP::print() {
	double checkSum = 0;
	for (auto i : m_path) {
		cout << i.first << " ";
		checkSum += i.second;
	}
	cout << "\n";
}