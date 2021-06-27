#pragma once
#include"Line.h"
#include"Point.h"
#include<cmath>
class Surface {
public:
	Surface() {}
	Surface(Point m1, Point m2, Point m3);
	Surface(Point a, Point vec);

	double getA() { return this->A; }
	double getB() { return this->B; }
	double getC() { return this->C; }
	double getD() { return this->D; }

	double* getVec(){
		double cv[3];
		double sum = A * A + B * B + C * C;
		cv[0] = sqrt((sum - B * B - C *C) / sum);
		cv[1] = sqrt((sum - A * A - C * C) / sum);
		cv[2] = sqrt((sum - B * B -A * A) / sum);
		return cv;
	}

private:
	//ax + by + cz + d = 0
	double A;
	double B;
	double C;
	double D;
};