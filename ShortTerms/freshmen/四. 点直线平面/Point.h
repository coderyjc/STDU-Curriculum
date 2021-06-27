#pragma once
class Point {
public:

	Point(double x = 0, double y = 0, double z = 0) :m_X(x), m_Y(y), m_Z(z) {}
	//Point(double x) : m_X(x), m_Y(0) {}
	//Point(double y) : m_Y(y), m_X(0) {}

	Point(const Point& p) {
		this->m_X = p.m_X;
		this->m_Y = p.m_Y;
		this->m_Z = p.m_Z;
	}

	Point operator*(Point p) {
		Point temp(this->m_Y * p.m_Z - this->m_Z * p.m_Y, this->m_Z * p.m_X - this->m_X * p.m_Z, this->m_X * p.m_Y - this->m_Y * p.m_X);;
		return temp;
	}

	Point operator-(Point p) {
		Point temp(this->m_X - p.m_X, this->m_Y - p.m_Y, this->m_Z - p.m_Z);
		return temp;
	}

	Point operator+(Point p) {
		Point temp(this->m_X + p.m_X, this->m_Y + p.m_Y, this->m_Z + p.m_Z);
		return temp;
	}

	//Point(const Point& p) {
	//	this->m_X = p.m_X;
	//	this->m_Y = p.m_Y;
	//	this->m_Z = p.m_Z;
	//}

	void setX(double x) { this->m_X = x; }
	void setY(double y) { this->m_Y = y; }
	void setZ(double z) { this->m_Z = z; }
	double getX() { return this->m_X; }
	double getY() { return this->m_Y; }
	double getZ() { return this->m_Z; }

private:
	double m_X;
	double m_Y;
	double m_Z;
};
