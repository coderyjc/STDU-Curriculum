#pragma once
#include"Point.h"
#include"Surface.h"
#include<algorithm>

class Surface;

class Line {
public:
	Line() {}

	Line(Point a, Point b);

	Line(Surface a, Surface b);

	double* getPosi() { return this->Position; }
	double* getVec() { return this->Vector; }
	double* getCountVec() {
		double cv[3];
		double sum = Vector[0] * Vector[0] + Vector[1] * Vector[1] + Vector[2] * Vector[2];
		cv[0] = sqrt((sum - Vector[1] * Vector[1] - Vector[2] * Vector[2]) / sum);
		cv[1] = sqrt((sum - Vector[0] * Vector[0] - Vector[2] * Vector[2]) / sum);
		cv[2] = sqrt((sum - Vector[1] * Vector[1] - Vector[0] * Vector[0]) / sum);
		return cv;
	}

private:

	/*
		x - x0  y - y0  z - z0
		------ = ------ = -----
		  m       n       p
	*/

	double Position[3];
	double Vector[3];
};