#include<iostream>
#include"Surface.h"
using namespace std;

void pointAndLine();
void pointAndSurface();
void lineAndLine();
void lineAndSurface();
void surfaceAndSurface();

Point inputPoint();
Line inputLine();
Surface inputSurface();

int main() {
	int choose;
	do {
		cout << ">空间点/线/面<" << endl
			<< "1. 点和线的关系 " << endl
			<< "2. 点和平面的关系 " << endl
			<< "3. 线和线的关系 " << endl
			<< "4. 线和平面的关系 " << endl
			<< "5. 平面和平面的关系 " << endl
			<< "0. 退出程序" << endl
			<< "请输入您想判断的类型：";
		cin >> choose;
		switch (choose) {
		case 1: pointAndLine(); break;
		case 2: pointAndSurface(); break;
		case 3: lineAndLine(); break;
		case 4: lineAndSurface(); break;
		case 5: surfaceAndSurface(); break;
		case 0: cout << "程序退出，感谢您的使用" << endl; break;
		default:cout << "输入有误，请重试" << endl; break;
		}
	} while (choose);
	return 0;
}

void pointAndLine() {
	Point p = inputPoint();
	Line l = inputLine();
	double* vec;
	double x, y, z;
	vec = l.getVec();
	cout << "线的方向向量：" << l.getCountVec()[0] << " " << l.getCountVec()[1] << " " << l.getCountVec()[2] << endl;
	if (vec[0] != 0) x = (p.getX() - l.getPosi()[0]) / l.getVec()[0];
	else x = 1;
	if(vec[1] != 0)  y = (p.getY() - l.getPosi()[1]) / l.getVec()[1];
	else y = 1;
	if(vec[2] != 0)  z = (p.getZ() - l.getPosi()[2]) / l.getVec()[2];
	else z = 1;
	if (x == y == z) cout << "点在直线上" << endl;
	else cout << "点在直线外" << endl;
	return;
}

void pointAndSurface() {
	Point p = inputPoint();
	Surface s = inputSurface();
	cout << "平面的法向量：" << s.getVec()[0] << " " << s.getVec()[1] << " " << s.getVec()[2] << endl;
	if (p.getX() * s.getA() + p.getY() * s.getB() + p.getZ() * s.getC() + s.getD() == 0)
		cout << "点在平面上" << endl;
	else
		cout << "点在平面外" << endl;
}

void lineAndLine() {
	Line l1 = inputLine();
	Line l2 = inputLine();
	double* vec = l2.getVec();
	double a, b, c;
	cout << "线的方向向量 l1 ：" << l1.getCountVec()[0] << " " << l1.getCountVec()[1] << " " << l1.getCountVec()[2] << endl;
	cout << "线的方向向量 l2 ：" << l2.getCountVec()[0] << " " << l2.getCountVec()[1] << " " << l2.getCountVec()[2] << endl;
	if (vec[0] == 0) a = 1;
	else a = l1.getVec()[0] / l2.getVec()[0];
	if (vec[1] == 0) b = 1;
	else b = l1.getVec()[1] / l2.getVec()[1];
	if (vec[2] == 0) c = 1;
	else c = l1.getVec()[2] / l2.getVec()[2];
	if (1 == a == b == c)
		cout << "两直线重合" << endl;
	else if (a == b == c)
		cout << "两直线平行" << endl;
	else cout << "两直线相交" << endl;
}

void lineAndSurface() {
	Line l = inputLine();
	Surface s = inputSurface();

	cout << "线的方向向量：" << l.getCountVec()[0] << " " << l.getCountVec()[1] << " " << l.getCountVec()[2] << endl;
	cout << "平面的法向量：" << s.getVec()[0] << " " << s.getVec()[1] << " " << s.getVec()[2] << endl;
	if (l.getVec()[0] * s.getA() + l.getVec()[1] * s.getB() + l.getVec()[2] * s.getC())
		cout << "直线与平面平行" << endl;
	else cout << "直线与平面相交" << endl;
}

void surfaceAndSurface() {
	Surface s1 = inputSurface();
	Surface s2 = inputSurface();
	cout << "平面的法向量 s1：" << s1.getVec()[0] << " " << s1.getVec()[1] << " " << s1.getVec()[2] << endl;
	cout << "平面的法向量 s2：" << s2.getVec()[0] << " " << s2.getVec()[1] << " " << s2.getVec()[2] << endl;
	double a = s1.getA() / s2.getA();
	double b = s1.getB() / s2.getB();
	double c = s1.getC() / s2.getC();
	double d = s1.getD() / s2.getD();
	if (1 == a == b == c == d)
		cout << "两平面重合" << endl;
	else if (a == b == c == d)
		cout << "两平面平行" << endl;
	else cout << "两平面相交" << endl;
}

Point inputPoint() {
	double x, y, z;
	cout << "请输入点的三个坐标（空格隔开）：";
	cin >> x >> y >> z;
	Point temp(x, y, z);
	return temp;
}

Line inputLine() {
	cout << "选择创建直线的方式" << endl
		<< "1. 两点确定一条直线" << endl
		<< "2. 两个平面的交线" << endl
		<< "请输入你的选择" << endl;
	int choose;
	cin >> choose;
	if (choose == 1) {
		cout << "第一个点" << endl;
		Point p1 = inputPoint();
		cout << "第二个点" << endl;
		Point p2 = inputPoint();
		Line temp(p1, p2);
		return temp;
	} else if (choose == 2) {
		cout << "第一个面" << endl;
		Surface s1 = inputSurface();
		cout << "第二个面" << endl;
		Surface s2 = inputSurface();
		Line temp(s1, s2);
		return temp;
	} else {
		cout << "输入有误, 程序终止" << endl;
		exit(0);
	}
}

Surface inputSurface() {
	cout << "选择创建方式" << endl
		<< "1. 三点确定一个平面" << endl
		<< "2. 点和向量确定一个平面" << endl
		<< "输入你的选择" << endl;
	int choose;
	cin >> choose;
	if (choose == 1) {
		cout << "第一个点" << endl;
		Point p1 = inputPoint();
		cout << "第二个点" << endl;
		Point p2 = inputPoint();
		cout << "第三个点" << endl;
		Point p3 = inputPoint();
		Surface temp(p1, p2, p3);
		return temp;
	} else if (choose == 2) {
		cout << "第一个点" << endl;
		Point p1 = inputPoint();
		cout << "第二个点" << endl;
		Point p2 = inputPoint();
		Surface temp(p1, p2);
		return temp;
	} else {
		cout << "输入有误, 程序终止" << endl;
		exit(0);
	}
}