// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#include "OPTTSP.hpp"

void OPTTSP::read() {
	//Normal Read
	FASTTSP::read();

	//Resize MST Stuff
	m_distanceMat.resize(m_vertices.size());
	m_minEdges.resize(m_vertices.size(), std::numeric_limits<double>::infinity());
	m_pathOpt.resize(m_vertices.size());
	m_path.reserve(m_vertices.size());
	m_visited.resize(m_vertices.size());

	//Create Distane Matrix to save time
	//[row][col]
	for (size_t i = 0; i < m_vertices.size(); ++i) {
		m_pathOpt[i] = (int)i;
		m_distanceMat[i].resize(m_vertices.size());
		for (size_t j = 0; j < m_vertices.size(); ++j) {
			m_distanceMat[i][j] = findDistance(i, j);
		}
	}

}

bool OPTTSP::promising(size_t permLength, double runningTotal) {
	//Reset MST vectors
	fill(m_minEdges.begin(), m_minEdges.end(), std::numeric_limits<double>::infinity());
	fill(m_visited.begin(), m_visited.end(), false);
	
	//Create MST of all points after permLength
	size_t currSmallest = permLength;
	double edgeTotal = 0;
	//Iterate over each point
	for (size_t i = permLength; i < m_pathOpt.size(); i++) {
		int nextSmallest = -1;

		//Check connection between each point and all other points
		for (size_t j = permLength; j < m_pathOpt.size(); j++) {

			//If not visited find the distance
			if (!m_visited[j]) {
				//If uninitialized set = to j
				if (nextSmallest == -1)
					nextSmallest = (int)j;

				double dist = m_distanceMat[m_pathOpt[currSmallest]][m_pathOpt[j]];

				//If found distance is smaller than the current distance
				if (dist < m_minEdges[j]) {
					m_minEdges[j] = dist; //Set min edge distance
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
	int end = m_pathOpt[permLength-1];

	for (size_t i = permLength; i < m_pathOpt.size(); ++i) {
		//Check if have better beginning index
		if (m_distanceMat[begin][m_pathOpt[i]] < beginBest)
			beginBest = m_distanceMat[begin][m_pathOpt[i]];
		if (m_distanceMat[end][m_pathOpt[i]] < endBest)
			endBest = m_distanceMat[end][m_pathOpt[i]];
	}

	//Check if not better than current best
	//cout << setw(10) << runningTotal << setw(10) << beginBest + endBest << setw(10) << edgeTotal << "\n";
	if (m_bestTotal < endBest + beginBest + runningTotal + edgeTotal)
		return false;
	return true;
	
}

void OPTTSP::genPerms( size_t permLength, double runningTotal) {
    //If we've reached the end of perm check if it's best perm yet
    if (permLength == m_pathOpt.size()) {
        if (runningTotal + m_distanceMat[0][m_pathOpt[permLength - 1]] < m_bestTotal) {
            //Need to add in edge between starting and ending point
            m_bestTotal = runningTotal + m_distanceMat[0][m_pathOpt[permLength-1]];
            m_bestPath = m_pathOpt;
        }
        return;
    } // if
    //If it isn't looking good then just return
    if (!promising(permLength, runningTotal))
        return;
    for (size_t i = permLength; i < m_pathOpt.size(); ++i) {
        swap(m_pathOpt[permLength], m_pathOpt[i]);
        genPerms( permLength + 1, runningTotal+m_distanceMat[m_pathOpt[permLength-1]][m_pathOpt[permLength]]);
        swap(m_pathOpt[permLength], m_pathOpt[i]);
    } // for
} // genPerms()

void OPTTSP::run() {
    
	FASTTSP::run();
	//Clear stuff from FASTTSP
	m_vertices.clear();
	m_path.clear();

	m_bestTotal = totalDist;
    //We start at root and current total is 0
    genPerms(1, 0);
	
}

void OPTTSP::print() {
	cout << m_bestTotal << "\n";
	for (auto i : m_bestPath)
		cout << i << " ";
	cout << "\n";
}