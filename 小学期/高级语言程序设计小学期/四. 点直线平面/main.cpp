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
		cout << ">�ռ��/��/��<" << endl
			<< "1. ����ߵĹ�ϵ " << endl
			<< "2. ���ƽ��Ĺ�ϵ " << endl
			<< "3. �ߺ��ߵĹ�ϵ " << endl
			<< "4. �ߺ�ƽ��Ĺ�ϵ " << endl
			<< "5. ƽ���ƽ��Ĺ�ϵ " << endl
			<< "0. �˳�����" << endl
			<< "�����������жϵ����ͣ�";
		cin >> choose;
		switch (choose) {
		case 1: pointAndLine(); break;
		case 2: pointAndSurface(); break;
		case 3: lineAndLine(); break;
		case 4: lineAndSurface(); break;
		case 5: surfaceAndSurface(); break;
		case 0: cout << "�����˳�����л����ʹ��" << endl; break;
		default:cout << "��������������" << endl; break;
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
	cout << "�ߵķ���������" << l.getCountVec()[0] << " " << l.getCountVec()[1] << " " << l.getCountVec()[2] << endl;
	if (vec[0] != 0) x = (p.getX() - l.getPosi()[0]) / l.getVec()[0];
	else x = 1;
	if(vec[1] != 0)  y = (p.getY() - l.getPosi()[1]) / l.getVec()[1];
	else y = 1;
	if(vec[2] != 0)  z = (p.getZ() - l.getPosi()[2]) / l.getVec()[2];
	else z = 1;
	if (x == y == z) cout << "����ֱ����" << endl;
	else cout << "����ֱ����" << endl;
	return;
}

void pointAndSurface() {
	Point p = inputPoint();
	Surface s = inputSurface();
	cout << "ƽ��ķ�������" << s.getVec()[0] << " " << s.getVec()[1] << " " << s.getVec()[2] << endl;
	if (p.getX() * s.getA() + p.getY() * s.getB() + p.getZ() * s.getC() + s.getD() == 0)
		cout << "����ƽ����" << endl;
	else
		cout << "����ƽ����" << endl;
}

void lineAndLine() {
	Line l1 = inputLine();
	Line l2 = inputLine();
	double* vec = l2.getVec();
	double a, b, c;
	cout << "�ߵķ������� l1 ��" << l1.getCountVec()[0] << " " << l1.getCountVec()[1] << " " << l1.getCountVec()[2] << endl;
	cout << "�ߵķ������� l2 ��" << l2.getCountVec()[0] << " " << l2.getCountVec()[1] << " " << l2.getCountVec()[2] << endl;
	if (vec[0] == 0) a = 1;
	else a = l1.getVec()[0] / l2.getVec()[0];
	if (vec[1] == 0) b = 1;
	else b = l1.getVec()[1] / l2.getVec()[1];
	if (vec[2] == 0) c = 1;
	else c = l1.getVec()[2] / l2.getVec()[2];
	if (1 == a == b == c)
		cout << "��ֱ���غ�" << endl;
	else if (a == b == c)
		cout << "��ֱ��ƽ��" << endl;
	else cout << "��ֱ���ཻ" << endl;
}

void lineAndSurface() {
	Line l = inputLine();
	Surface s = inputSurface();

	cout << "�ߵķ���������" << l.getCountVec()[0] << " " << l.getCountVec()[1] << " " << l.getCountVec()[2] << endl;
	cout << "ƽ��ķ�������" << s.getVec()[0] << " " << s.getVec()[1] << " " << s.getVec()[2] << endl;
	if (l.getVec()[0] * s.getA() + l.getVec()[1] * s.getB() + l.getVec()[2] * s.getC())
		cout << "ֱ����ƽ��ƽ��" << endl;
	else cout << "ֱ����ƽ���ཻ" << endl;
}

void surfaceAndSurface() {
	Surface s1 = inputSurface();
	Surface s2 = inputSurface();
	cout << "ƽ��ķ����� s1��" << s1.getVec()[0] << " " << s1.getVec()[1] << " " << s1.getVec()[2] << endl;
	cout << "ƽ��ķ����� s2��" << s2.getVec()[0] << " " << s2.getVec()[1] << " " << s2.getVec()[2] << endl;
	double a = s1.getA() / s2.getA();
	double b = s1.getB() / s2.getB();
	double c = s1.getC() / s2.getC();
	double d = s1.getD() / s2.getD();
	if (1 == a == b == c == d)
		cout << "��ƽ���غ�" << endl;
	else if (a == b == c == d)
		cout << "��ƽ��ƽ��" << endl;
	else cout << "��ƽ���ཻ" << endl;
}

Point inputPoint() {
	double x, y, z;
	cout << "���������������꣨�ո��������";
	cin >> x >> y >> z;
	Point temp(x, y, z);
	return temp;
}

Line inputLine() {
	cout << "ѡ�񴴽�ֱ�ߵķ�ʽ" << endl
		<< "1. ����ȷ��һ��ֱ��" << endl
		<< "2. ����ƽ��Ľ���" << endl
		<< "���������ѡ��" << endl;
	int choose;
	cin >> choose;
	if (choose == 1) {
		cout << "��һ����" << endl;
		Point p1 = inputPoint();
		cout << "�ڶ�����" << endl;
		Point p2 = inputPoint();
		Line temp(p1, p2);
		return temp;
	} else if (choose == 2) {
		cout << "��һ����" << endl;
		Surface s1 = inputSurface();
		cout << "�ڶ�����" << endl;
		Surface s2 = inputSurface();
		Line temp(s1, s2);
		return temp;
	} else {
		cout << "��������, ������ֹ" << endl;
		exit(0);
	}
}

Surface inputSurface() {
	cout << "ѡ�񴴽���ʽ" << endl
		<< "1. ����ȷ��һ��ƽ��" << endl
		<< "2. �������ȷ��һ��ƽ��" << endl
		<< "�������ѡ��" << endl;
	int choose;
	cin >> choose;
	if (choose == 1) {
		cout << "��һ����" << endl;
		Point p1 = inputPoint();
		cout << "�ڶ�����" << endl;
		Point p2 = inputPoint();
		cout << "��������" << endl;
		Point p3 = inputPoint();
		Surface temp(p1, p2, p3);
		return temp;
	} else if (choose == 2) {
		cout << "��һ����" << endl;
		Point p1 = inputPoint();
		cout << "�ڶ�����" << endl;
		Point p2 = inputPoint();
		Surface temp(p1, p2);
		return temp;
	} else {
		cout << "��������, ������ֹ" << endl;
		exit(0);
	}
}