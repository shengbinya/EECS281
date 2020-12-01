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

bool FASTTSP::doesIntersect(const size_t t_l11, const size_t t_l12,
	const size_t t_l21, const size_t t_l22) {
	Point one = m_vertices[t_l11] - m_vertices[t_l21];
	Point two = m_vertices[t_l22] - m_vertices[t_l21];
	int d1 = one * two;

	Point three = m_vertices[t_l12] - m_vertices[t_l21];
	int d2 = three * two;
	
	Point four = m_vertices[t_l12] - m_vertices[t_l11];
	int d3 = (one * -1) * four;

	Point five = m_vertices[t_l22] - m_vertices[t_l11];
	int d4 = five * four;
	
	if (((d1 < 0 && d2 > 0) || (d1 > 0 && d2 < 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true;

	return false;
}

void FASTTSP::run() {
	//Add first cycle
	double dist = findDistance(0, 1);
	m_path.push_back(pair<int, double>{ 0, dist });
	m_path.push_back(pair<int, double>{ 1, dist });
	totalDist = 2 * dist;

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
		m_path.insert(m_path.begin() + minIndex + 1, pair<int, double>{i, newDistR});
		totalDist += newDistL + newDistR;
	}

	/*
	//2-Opt Algorithm
	//Check for intersection at beginning
	size_t end = m_path.size() - 1;
	if (doesIntersect(m_path[1].first, m_path[2].first, m_path[m_path.size()-1].first, m_path[0].first)) {

		//Update Distances
		totalDist -= m_path[1].second + m_path[end].second;
		double newDistR = findDistance(m_path[end].first, m_path[1].first);
		double newDistL = findDistance(m_path[0].first, m_path[2].first);
		totalDist += newDistR + newDistL;
		m_path[1].second = m_path[0].second;
		swap(m_path[0], m_path[1]);
		m_path[end].second = newDistR;
		m_path[1].second = newDistL;
			
	}
	
	for (size_t i = 0; i < m_path.size() - 1; ++i) {
		for (size_t j = i + 2; j < m_path.size()-1; ++j) {
			if (doesIntersect(m_path[i].first, m_path[i + 1].first, m_path[j].first, m_path[j + 1].first)) {

				//Update Distances
				totalDist -= m_path[i].second + m_path[j].second;
				double newDistR = findDistance(m_path[i].first, m_path[j + 1].first);
				double newDistL = findDistance(m_path[i + 1].first, m_path[j].first);
				totalDist += newDistR + newDistL;
				m_path[i].second = newDistR;
				m_path[j].second = newDistL;

				//Iterate through half and swap elements
				size_t l = j;
				for (size_t k = i + 1; k <= (i + 1 + j) / 2; ++k) {
					swap(m_path[k], m_path[l]);
					--l;
				}
			}

		}
	
	}
	*/
	
	
	
}

void FASTTSP::print() {
	cout << totalDist << "\n";
	for (auto i : m_path) {
		cout << i.first << " ";
	}
	cout << "\n";
}