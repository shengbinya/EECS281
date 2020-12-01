// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#pragma once
#include "FASTTSP.hpp"

class OPTTSP : public FASTTSP {

private:
	vector<vector<double>> m_distanceMat;
	vector<double> m_minEdges;
	vector<int> m_path;
	vector<int> m_bestPath;
	vector<bool> m_visited;
	double m_bestTotal = std::numeric_limits<double>::infinity();
	
public:

	OPTTSP() {}

	void read() override;

	void run() override;

	void genPerms(size_t, double);
	
	bool promising(size_t, double);

	void print() override;

};