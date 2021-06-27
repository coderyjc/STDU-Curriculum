#include "Line.h"
#include<cmath>

Line::Line(Point a, Point b) {
//point and its tangent
	//法向量
	this->Vector[0] = a.getX() - b.getX();
	this->Vector[1] = a.getY() - b.getY();
	this->Vector[2] = a.getZ() - b.getZ();

	// 初始坐标
	this->Position[0] = a.getX();
	this->Position[1] = a.getY();
	this->Position[2] = a.getZ();
}

Line::Line(Surface a, Surface b) {

	//只能确定一个直线系， 而不是一条直线
	Vector[0] = a.getB() * b.getC() - a.getC() * b.getB();
	Vector[1] = a.getC() * b.getA() - a.getA() * b.getC();
	Vector[2] = a.getA() * b.getB() - a.getB() * b.getA();
}