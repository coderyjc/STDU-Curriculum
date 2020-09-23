#pragma once
class Point {
public:

	Point(double x = 0, double y = 0) :m_X(x), m_Y(y) {}

	void setX(double x) { this->m_X = x; }
	void setY(double y) { this->m_Y = y; }
	double getX() { return this->m_X; }
	double getY() { return this->m_Y; }


private:
	double m_X;
	double m_Y;
};
