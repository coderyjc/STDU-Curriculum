#pragma once
#include"Point.h"
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

class Triangle {
public:
	Triangle(Point x, Point y, Point z) : m_A(x), m_B(y), m_C(z) {}

	void calculateLength() {
		this->Length[0] = sqrt(pow(m_B.getX() - m_C.getX(), 2) + pow(m_B.getY() - m_C.getY(), 2));
		this->Length[1] = sqrt(pow(m_A.getX() - m_C.getX(), 2) + pow(m_A.getY() - m_C.getY(), 2));
		this->Length[2] = sqrt(pow(m_B.getX() - m_A.getX(), 2) + pow(m_B.getY() - m_A.getY(), 2));
	}

	void typeJudge(int pre = 3){
		this->calculateLength();
		sort(this->Length, this->Length + 3);
		if (Length[0] + Length[1] <= Length[2]) {
			cout << "三边不能构成三角形" << endl;
			return;
		}
		cout << "三角形三边的长度为 ：" << Length[0] << " " << Length[1] << " " << Length[2] << endl; // test !!!
		cout << "三角形三边的平方为 ：" << pow(Length[0], 2) << " " << pow(Length[1], 2) << " " << pow(Length[2], 2) << endl;
		double PERCISION = 1.0 / pow(10, pre);
		cout << "精确度为 ：" << PERCISION << endl;
		int isAcute = 0;  //锐角三角形
		int isRight = 0;  //直角三角形
		int isObtuse = 0; //钝角三角形
		int isEquicrural = 0; //等腰三角形
		int isEquilateral  = 0; //等边三角形
		double result = pow(Length[0], 2) + pow(Length[1], 2) - pow(Length[2], 2); // a^2 + b^2 - c^2
		if (Length[2] - Length[0] <= PERCISION) isEquilateral = 1;
		if (Length[1] - Length[0] <= PERCISION || Length[2] - Length[1] <= PERCISION) isEquicrural = 1;
		if (fabs(result) <= PERCISION) isRight = 1;
		if (result > PERCISION) isAcute = 1;
		if (result < -PERCISION) isObtuse = 1;
		
		cout << "判定结果为 ：" << endl;
		if (isEquilateral) {
			cout << "等边三角形" << endl;
			return;
		}
		if (isEquicrural) cout << "等腰三角形" << endl;
		if (isAcute)cout << "锐角三角形" << endl;
		if (isObtuse) cout << "钝角三角形" << endl;
		if (isRight) cout << "直角三角形" << endl;
	}

private:
	Point m_A;
	Point m_B;
	Point m_C;
	double Length[3];
};

