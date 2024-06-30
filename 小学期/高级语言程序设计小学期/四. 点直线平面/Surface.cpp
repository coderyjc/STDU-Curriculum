#include "Surface.h"

Surface::Surface(Point a, Point m2, Point m3) {

	Point vec1 = m2 - a;
	Point vec2 = m3 - a;
	Point vec = vec1 * vec2;
	this->A = vec.getX();
	this->B = vec.getY();
	this->C = vec.getZ();
	this->D = -vec.getX() * a.getX() - vec.getY() * a.getY() - vec.getZ() * a.getZ();
}

Surface::Surface(Point a, Point vec) {
	this->A = vec.getX();
	this->B = vec.getY();
	this->C = vec.getZ();
	this->D = -vec.getX() * a.getX() - vec.getY() * a.getY() - vec.getZ() * a.getZ();
}
