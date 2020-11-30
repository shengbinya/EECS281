// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "OPTTSP.hpp"

void OPTTSP::read() {
	//Normal Read
	FASTTSP::read();

	//Resize MST Stuff
	m_distanceMat.resize(m_vertices.size());
	m_minEdges.resize(m_vertices.size(), std::numeric_limits<double>::infinity());
	m_path.resize(m_vertices.size());
	m_preVertex.resize(m_vertices.size());
	m_visited.resize(m_vertices.size());

	//Create Distane Matrix to save time
	//[row][col]
	for (size_t i = 0; i < m_vertices.size(); ++i) {
		m_path[i] = (int)i;
		m_distanceMat[i].resize(m_vertices.size());
		for (size_t j = 0; j < m_vertices.size(); ++j) {
			m_distanceMat[i][j] = findDistance(i, j);
		}
	}
	m_vertices.clear();

}

bool OPTTSP::promising(size_t permLength, double runningTotal) {
	//Reset MST vectors
	fill(m_minEdges.begin(), m_minEdges.end(), std::numeric_limits<double>::infinity());
	fill(m_preVertex.begin(), m_preVertex.end(), 0);
	fill(m_visited.begin(), m_visited.end(), false);
	
	//Create MST of all points after permLength
	int currSmallest = 0;
	double edgeTotal = 0;
	//Iterate over each point
	for (size_t i = permLength+1; i < m_path.size(); i++) {
		int nextSmallest = -1;

		//Check connection between each point and all other points
		for (size_t j = permLength+1; j < m_path.size(); j++) {

			//If not visited find the distance
			if (!m_visited[j]) {
				//If uninitialized set = to j
				if (nextSmallest == -1)
					nextSmallest = (int)j;

				double dist = m_distanceMat[currSmallest][m_path[j]];

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

	//Find shortest edge in MST to end points
	double beginBest = std::numeric_limits<double>::infinity();
	double endBest = std::numeric_limits<double>::infinity();
	int begin = 0;
	int end = m_path[permLength];

	for (size_t i = size_t(permLength + 1); i < m_vertices.size(); ++i) {
		//Check if have better beginning index
		if (m_distanceMat[begin][m_path[i]] < beginBest)
			beginBest = m_distanceMat[begin][m_path[i]];
		if (m_distanceMat[end][m_path[i]] < endBest)
			endBest = m_distanceMat[end][m_path[i]];
	}

	//Check if not better than current best
	if (m_bestTotal < endBest + beginBest + runningTotal + edgeTotal)
		return false;
	return true;
	
}

void OPTTSP::genPerms( size_t permLength, double runningTotal) {
    //If we've reached the end of perm check if it's best perm yet
    if (permLength == m_path.size()) {
        if (runningTotal < m_bestTotal) {
            //Need to add in edge between starting and ending point
            m_bestTotal = runningTotal + m_distanceMat[0][m_path.size()-1];
            m_bestPath = m_path;
        }
        return;
    } // if
    //If it isn't looking good then just return
    if (!promising(permLength, runningTotal))
        return;
    for (size_t i = permLength; i < m_path.size(); ++i) {
        swap(m_path[permLength], m_path[i]);
        genPerms( permLength + 1, runningTotal+m_distanceMat[permLength-1][permLength]);
        swap(m_path[permLength], m_path[i]);
    } // for
} // genPerms()

void OPTTSP::run() {
    
    //We start at root and current total is 0
    genPerms(1, 0);
	
}

void OPTTSP::print() {
	cout << m_bestTotal << "\n";
	for (auto i : m_path)
		cout << i << " ";
	cout << "\n";
}