// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
#pragma once
#include "PathFinder.hpp"

class FASTTSP : public PathFinder{

private:
	friend class OPTTSP;

	vector<pair<int, double>> m_path;
	vector<Point> m_vertices;
	double totalDist;

public:

	//Default Constructor
	FASTTSP() {}

	void read() override;

	double findDistance(const size_t, const size_t) override;

	void run() override;

	void print() override;

	bool doesIntersect(const size_t t_l11, const size_t t_l12,
		const size_t t_l21, const size_t t_l22);
};